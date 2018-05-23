open Discord;

type t =
  | Ping
  | Roll(array(Roller.token))
  | Help
  | Get
  | Set(string)
  | EightBall
  | Giphy(string)
  | Poll
  | PollRange(int, int)
  | Update
  | TakPlay(Tak.action)
  | TakShow;

module Parser = {
  let parseTakPosition = (columnString, rowString) => {
    let column = Utils.parseInt(0, columnString) - 1;
    let row =
      int_of_float(
        Js.String.charCodeAt(0, Js.String.toUpperCase(rowString))
        -. Js.String.charCodeAt(0, "A"),
      );
    Tak.position(column, row);
  };
  let parseTakPlace = args =>
    args
    |> Js.String.match(
         Js.Re.fromStringWithFlags("^(c|f|s)?\\s*(\\d)([A-Z])$", ~flags="i"),
       )
    |> Belt.Option.mapU(
         _,
         (. match_) => {
           let stoneType =
             switch (
               Utils.truthy(match_[1]) ?
                 Js.String.toUpperCase(match_[1]) : ""
             ) {
             | "C" => Tak.Capstone
             | "S" => Tak.StandingStone
             | _ => Tak.FlatStone
             };
           let position = parseTakPosition(match_[2], match_[3]);
           TakPlay(Tak.Place(stoneType, position));
         },
       );
  let parseTakMove = args =>
    args
    |> Js.String.match(
         Js.Re.fromStringWithFlags(
           "^(\\d)([A-Z]) ([NESW])((?:\\s+\\d+)+)$",
           ~flags="i",
         ),
       )
    |> Belt.Option.mapU(
         _,
         (. match_) => {
           let position = parseTakPosition(match_[1], match_[2]);
           let direction =
             switch (Js.String.toUpperCase(match_[3])) {
             | "N" => Tak.North
             | "E" => Tak.East
             | "S" => Tak.South
             | "W" => Tak.West
             | _ => failwith("Unknown direction " ++ match_[3])
             };
           let leftStones =
             Tak.leftStones(
               Js.String.splitByRe(
                 Js.Re.fromString("\\s+"),
                 Js.String.trim(match_[4]),
               )
               |> Belt.Array.mapU(_, (. value) => Utils.parseInt(0, value))
               |> Belt.List.fromArray,
             );
           TakPlay(Tak.Move(position, direction, leftStones));
         },
       );
  /* | (stoneType, position)
     | Move(position, direction, leftStones); */
  let parseTak = args =>
    args
    |> Js.String.match(
         Js.Re.fromStringWithFlags(
           "^(place|move|show)\\b\\s*(.*)$",
           ~flags="i",
         ),
       )
    |> Belt.Option.flatMapU(_, (. match_) =>
         switch (match_[1]) {
         | "place" => parseTakPlace(match_[2])
         | "move" => parseTakMove(match_[2])
         | "show" => Some(TakShow)
         | _ => None
         }
       );
  let parseMatch = (commandName, args) =>
    switch (commandName) {
    | "ping" => Some(Ping)
    | "roll" => Roller.parseRoll(args) |> Belt.Option.map(_, x => Roll(x))
    | "help" => Some(Help)
    | "get" => Some(Get)
    | "set" => Some(Set(args))
    | "8ball" => Some(EightBall)
    | "giphy" => Some(Giphy(args))
    | "poll" =>
      args
      |> Js.String.match(Js.Re.fromString("^(\\d+)(?:-(\\d+))?\\b"))
      |> (
        match_ =>
          switch (match_) {
          | None => Some(Poll)
          | Some(match_) =>
            if (match_[2] |> Utils.truthy) {
              Some(
                PollRange(
                  Utils.parseInt(1, match_[1]),
                  Utils.parseInt(10, match_[2]),
                ),
              );
            } else {
              Some(PollRange(1, Utils.parseInt(10, match_[1])));
            }
          }
      )
    | "update" => Some(Update)
    | "tak" => parseTak(args)
    | _ => None
    };
  let parseContent = (prefix, client, content) =>
    content
    |> Js.String.match(
         Js.Re.fromString(
           "^(?:<@"
           ++ (
             Discord.Client.user(client)
             |> Belt.Option.getExn
             |> Discord.ClientUser.id
             |> Discord.Snowflake.toString
           )
           ++ ">[,:]?\\s*|"
           ++ prefix
           ++ ")(\\S+)\\s*(.*)",
         ),
       )
    |> Belt.Option.flatMap(_, match_ =>
         parseMatch(match_[1] |> Js.String.toLowerCase, match_[2])
       );
  let parsePrefixedMessage = (prefix, client, msg) =>
    parseContent(prefix, client, msg |> Message.content |> Js.String.trim);
  let parseDirectMessage = parsePrefixedMessage("~?");
  let parseChannelMessage = parsePrefixedMessage("~");
  let parseMessage = (client, msg) =>
    switch (msg |> Message.channel |> Channel.channelType) {
    | "dm" => parseDirectMessage(client, msg)
    | "text" => parseChannelMessage(client, msg)
    | _ => None
    };
};

let parseMessage = Parser.parseMessage;

module Handler = {
  let engine = Random.MersenneTwister.(make() |> autoSeed |> engine);
  let help = msg => {
    let _ =
      msg
      |> Message.reply(
           [|
             "~roll d20 + 4d10 - 2d6 + 3dF + 5",
             "~8ball",
             "~giphy cats",
             "~poll [[min-]max] [topic]",
           |]
           |> Js.Array.joinWith("\n"),
         );
    ();
  };
  let ping = msg => {
    Js.log("ping from " ++ User.username(Message.author(msg)));
    let _ = msg |> Message.reply("pong!");
    ();
  };
  let roll = (data, msg) => {
    State.UserState.update(Message.author(msg), state =>
      {...state, rolls: state.rolls + 1}
    );
    Js.log(
      "roll from "
      ++ User.username(Message.author(msg))
      ++ " "
      ++ Roller.stringify(data),
    );
    let rolls = Roller.roll(data, engine);
    let _ =
      msg
      |> Message.reply(
           ~split=SplitOptions.make(),
           Roller.emojify(data, rolls)
           ++ " = "
           ++ Js.String.make(Roller.calculateTotal(data, rolls)),
         );
    ();
  };
  let eightBall = msg => EightBall.handle(engine, msg);
  let get = msg => {
    let state = State.UserState.get(Message.author(msg));
    let _ = msg |> Message.reply(state.note);
    ();
  };
  let set = (note, msg) => {
    State.UserState.update(Message.author(msg), state => {...state, note});
    let _ = msg |> Message.reply("note = " ++ note);
    ();
  };
  let giphy = (search, msg) => {
    let client = Giphy.makeClient();
    let _ =
      client
      |> Giphy.random(search)
      |> Js.Promise.then_(url => msg |> Message.reply(url));
    ();
  };
  let poll = msg => {
    let _ =
      msg
      |> Message.reactWithString({js|👍|js})
      |> Js.Promise.then_((_) =>
           msg |> Message.reactWithString({js|👎|js})
         )
      |> Js.Promise.then_((_) =>
           msg |> Message.reactWithString({js|🤷|js})
         );
    ();
  };
  let pollRange = (start, finish, msg) => {
    let isValidRange = x => x >= 1 && x <= 10;
    let getEmojiStringForInt = x =>
      switch (x) {
      | 1 => {js|1⃣|js}
      | 2 => {js|2⃣|js}
      | 3 => {js|3⃣|js}
      | 4 => {js|4⃣|js}
      | 5 => {js|5⃣|js}
      | 6 => {js|6⃣|js}
      | 7 => {js|7⃣|js}
      | 8 => {js|8⃣|js}
      | 9 => {js|9⃣|js}
      | 10 => {js|🔟|js}
      | _ => failwith("Unexpected value")
      };
    if (isValidRange(start) && isValidRange(finish) && start <= finish) {
      let rec run = i =>
        if (i <= finish) {
          msg
          |> Message.reactWithString(getEmojiStringForInt(i))
          |> Js.Promise.then_((_) => run(i + 1));
        } else {
          Js.Promise.resolve();
        };
      let _ = run(start);
      ();
    };
  };
  let update = msg => {
    let result =
      Node.Child_process.execSync(
        "git pull && yarn install --ignore-scripts",
        Node.Child_process.option(~encoding="utf8", ()),
      );
    let _ = msg |> Message.reply(result);
    ();
  };
  let takGame = ref(Tak.create(5));
  let showTak = board => {
    ();
    let size = Tak.boardSize(board);
    (
      switch (Tak.whoseTurn(board)) {
      | Some(Tak.Black) => "Black's turn"
      | Some(Tak.White) => "White's turn"
      | None => "Nobody's turn"
      }
    )
    ++ "\n"
    ++ (
      Belt.Array.range(0, size - 1)
      |> Belt.Array.mapU(_, (. row) =>
           Belt.Array.range(0, size - 1)
           |> Belt.Array.mapU(
                _,
                (. column) => {
                  let pieces = Tak.pieces(Tak.position(column, row), board);
                  switch (pieces) {
                  | [(color, stoneType), ..._] =>
                    switch (color, stoneType) {
                    | (Tak.Black, Tak.Capstone) => {js|🌚|js}
                    | (Tak.Black, Tak.StandingStone) => {js|●|js}
                    | (Tak.Black, Tak.FlatStone) => {js|◾|js}
                    | (Tak.White, Tak.Capstone) => {js|🌝|js}
                    | (Tak.White, Tak.StandingStone) => {js|○|js}
                    | (Tak.White, Tak.FlatStone) => {js|◽|js}
                    }
                  | [] => {js|🕳️|js}
                  };
                },
              )
           |> Js.Array.joinWith("")
         )
      |> Js.Array.joinWith("\n")
    );
  };
  let playTak = (action, msg) => {
    switch (Tak.dispatch(action, takGame^)) {
    | Belt.Result.Ok(newGame) =>
      takGame := newGame;
      let _ = msg |> Message.reply(showTak(takGame^));
      ();
    | Belt.Result.Error(reason) =>
      let _ = msg |> Message.reply(reason);
      ();
    };
    ();
  };
  let handleMessage = (msg, command) =>
    switch (command) {
    | Help => help(msg)
    | Ping => ping(msg)
    | Roll(data) => roll(data, msg)
    | EightBall => eightBall(msg)
    | Get => get(msg)
    | Set(note) => set(note, msg)
    | Giphy(search) => giphy(search, msg)
    | Poll => poll(msg)
    | PollRange(start, finish) => pollRange(start, finish, msg)
    | Update => update(msg)
    | TakPlay(action) => playTak(action, msg)
    | TakShow => ignore(msg |> Message.reply(showTak(takGame^)))
    };
};

let handleMessage = Handler.handleMessage;
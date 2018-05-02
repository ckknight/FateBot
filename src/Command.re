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
  | Update;

module Parser = {
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
           ++ ">\\s*|"
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
    };
};

let handleMessage = Handler.handleMessage;
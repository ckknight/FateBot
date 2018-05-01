open Discord;

open Utils;

let maxDiceCount = 100.;

let client = Client.make();

type role =
  | Admin
  | Normie
  | Fucker
  | Bot;

let role_of_user = user =>
  if (user |> User.bot) {
    Bot;
  } else {
    switch (user |> User.username) {
    | "ckknight" => Admin
    | "Blaine66" => Fucker
    | "FalconWiz" => Fucker
    | _ => Normie
    };
  };

let handleAdminMessage = msg => {
  let author = Message.author(msg);
  switch (msg |> Message.content |> Js.String.toLowerCase) {
  | "ping" =>
    Js.log("channel " ++ Channel.channelType(Message.channel(msg)));
    Js.log("ping! pong. " ++ Snowflake.toString(User.id(author)));
    let _ = msg |> Message.reply("pong");
    ();
  | _ => ()
  };
};

let handleNormieMessage = msg => {
  let author = Message.author(msg);
  switch (msg |> Message.content |> Js.String.toLowerCase) {
  | "ping" =>
    Js.log("channel " ++ Channel.channelType(Message.channel(msg)));
    Js.log("ping! pong. " ++ Snowflake.toString(User.id(author)));
    let _ = msg |> Message.reply("pong");
    ();
  | _ => ()
  };
};

let handleFuckerMessage = msg =>
  switch (msg |> Message.content |> Js.String.toLowerCase) {
  | "ping" =>
    let _ = msg |> Message.reply("kys, fucker");
    ();
  | _ => ()
  };

type command =
  | Ping
  | Roll(Roller.t)
  | Help
  | Get
  | Set(string)
  | EightBall
  | Giphy(string)
  | Poll
  | PollRange(int, int)
  | Update;

let parseMatch = (commandName, args) =>
  switch (commandName) {
  | "ping" => Some(Ping)
  | "roll" => Roller.parseRoll(args) |> Option.map(x => Roll(x))
  | "help" => Some(Help)
  | "get" => Some(Get)
  | "set" => Some(Set(args))
  | "8ball" => Some(EightBall)
  | "giphy" => Some(Giphy(args))
  | "poll" =>
    args
    |> Js.String.match(Js.Re.fromString("^(\\d+)(?:-(\\d+))?\\s+"))
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

let parseContent = (prefix, content) =>
  content
  |> Js.String.match(Js.Re.fromString("^" ++ prefix ++ "(\\S+)\\s*(.*)"))
  |> (
    match_ =>
      switch (match_) {
      | None => None
      | Some(match_) =>
        parseMatch(match_[1] |> Js.String.toLowerCase, match_[2])
      }
  );

let parsePrefixedMessage = (prefix, msg) =>
  parseContent(prefix, msg |> Message.content |> Js.String.trim);

let parseDirectMessage = parsePrefixedMessage("~?");

let parseChannelMessage = parsePrefixedMessage("~");

let parseMessage = msg =>
  switch (msg |> Message.author |> role_of_user) {
  | Bot => None
  | _ =>
    switch (msg |> Message.channel |> Channel.channelType) {
    | "dm" => parseDirectMessage(msg)
    | "text" => parseChannelMessage(msg)
    | _ => None
    }
  };

let engine = Random.MersenneTwister.(make() |> autoSeed |> engine);

let logMessage = msg => {
  let author = msg |> Message.author;
  let channel = msg |> Message.channel;
  let channelName =
    switch (channel |> Channel.classify) {
    | Channel.DM(_) => "DM"
    | Channel.Group(_) => "Group DM"
    | Channel.Text(textChannel) =>
      (textChannel |> TextChannel.guild |> Guild.name)
      ++ " #"
      ++ TextChannel.name(textChannel)
    | Channel.Voice(_) => "Voice"
    };
  let fullUsername =
    "@" ++ User.username(author) ++ "#" ++ User.discriminator(author);
  let content = msg |> Message.content;
  Js.log(channelName ++ ": " ++ fullUsername ++ "> " ++ content);
};

type eightBallMood =
  | Affirmative
  | Noncommittal
  | Negative;

let eightBallResults = [|
  (Affirmative, "It is certain"),
  (Affirmative, "It is decidedly so"),
  (Affirmative, "Without a doubt"),
  (Affirmative, "Yes definitely"),
  (Affirmative, "You may rely on it"),
  (Affirmative, "As I see it, yes"),
  (Affirmative, "Most likely"),
  (Affirmative, "Outlook good"),
  (Affirmative, "Yes"),
  (Affirmative, "Signs point to yes"),
  (Noncommittal, "Reply hazy try again"),
  (Noncommittal, "Ask again later"),
  (Noncommittal, "Better not tell you now"),
  (Noncommittal, "Cannot predict now"),
  (Noncommittal, "Concentrate and ask again"),
  (Negative, "Don't count on it"),
  (Negative, "My reply is no"),
  (Negative, "My sources say no"),
  (Negative, "Outlook not so good"),
  (Negative, "Very doubtful"),
|];

let handleMessage = msg => {
  logMessage(msg);
  parseMessage(msg)
  |> Option.iter(command =>
       switch (command) {
       | Help =>
         Js.log("help from " ++ User.username(Message.author(msg)));
         let _ = msg |> Message.reply("~roll d20 + 4d10 - 2d6 + 3dF + 5");
         ();
       | Ping =>
         Js.log("ping from " ++ User.username(Message.author(msg)));
         let _ = msg |> Message.reply("pong");
         ();
       | Roll(data) =>
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
       | EightBall =>
         let (mood, text) =
           Random.pick(eightBallResults, engine)
           |> Utils.Option.orRaise(Failure("Expected a result"));
         let _ =
           msg
           |> Message.reply(
                text
                ++ " "
                ++ (
                  switch (mood) {
                  | Affirmative => ":+1:"
                  | Noncommittal => ":shrug:"
                  | Negative => ":-1:"
                  }
                ),
              );
         ();
       | Get =>
         let state = State.UserState.get(Message.author(msg));
         let _ = msg |> Message.reply(state.note);
         ();
       | Set(note) =>
         State.UserState.update(Message.author(msg), state =>
           {...state, note}
         );
         let _ = msg |> Message.reply("note = " ++ note);
         ();
       | Giphy(search) =>
         let client = Giphy.makeClient();
         let _ =
           client
           |> Giphy.random(search)
           |> Js.Promise.then_(url => msg |> Message.reply(url));
         ();
       | Poll =>
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
       | PollRange(start, finish) =>
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
       | Update =>
         let result =
           Node.Child_process.execSync(
             "git pull && yarn install --ignore-scripts",
             Node.Child_process.option(~encoding="utf8", ()),
           );
         msg |> Message.reply(result) |> ignore;
         ();
       }
     );
};

client |> Client.onError(exn => Js.log(exn));

client
|> Client.onReady(() => {
     client
     |> Client.user
     |> Option.orRaise(Failure("expected a user"))
     |> ClientUser.setPresence(~game="~help")
     |> promiseMap(stuff => Js.log(stuff))
     |> promiseEnd;
     Js.log("Bot is ready!");
   });

client |> Client.onMessage(handleMessage);

let token = Node.Fs.readFileAsUtf8Sync("./token.txt") |> Js.String.trim;

client |> Client.login(token);
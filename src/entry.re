open Discord;

open Utils;

let maxDiceCount = 100.;

let client = Client.make();

type role =
  | Admin
  | Normie
  | Fucker
  | Bot;

let role_of_user (user) =
  if (user |> User.bot) {
    Bot
  } else {
    switch (user |> User.username) {
    | "ckknight" => Admin
    | "Blaine66" => Fucker
    | "FalconWiz" => Fucker
    | _ => Normie
    }
  };

let handleAdminMessage (msg) = {
  let author = Message.author(msg);
  switch (msg |> Message.content |> Js.String.toLowerCase) {
  | "ping" =>
    Js.log("channel " ++ Channel.channelType(Message.channel(msg)));
    Js.log("ping! pong. " ++ Snowflake.toString(User.id(author)));
    let _ = msg |> Message.reply("pong");
    ()
  | _ => ()
  }
};

let handleNormieMessage (msg) = {
  let author = Message.author(msg);
  switch (msg |> Message.content |> Js.String.toLowerCase) {
  | "ping" =>
    Js.log("channel " ++ Channel.channelType(Message.channel(msg)));
    Js.log("ping! pong. " ++ Snowflake.toString(User.id(author)));
    let _ = msg |> Message.reply("pong");
    ()
  | _ => ()
  }
};

let handleFuckerMessage (msg) =
  switch (msg |> Message.content |> Js.String.toLowerCase) {
  | "ping" =>
    let _ = msg |> Message.reply("kys, fucker");
    ()
  | _ => ()
  };

type command =
  | Ping
  | Roll(Roller.t)
  | Help
  | Get
  | Set(string)
  | EightBall;

let parseMatch (commandName, args) =
  switch (commandName) {
  | "ping" => Some(Ping)
  | "roll" => Roller.parseRoll(args) |> Option.map((x) => Roll(x))
  | "help" => Some(Help)
  | "get" => Some(Get)
  | "set" => Some(Set(args))
  | "8ball" => Some(EightBall)
  | _ => None
  };

let parseContent (prefix, content) =
  content
  |> Js.String.match_(Js.Re.fromString("^" ++ prefix ++ "(\\S+)\\s*(.*)"))
  |> (
    (match_) =>
      switch (match_) {
      | None => None
      | Some(match_) =>
        parseMatch(match_[1] |> Js.String.toLowerCase, match_[2])
      }
  );

let parsePrefixedMessage (prefix, msg) =
  parseContent(prefix, msg |> Message.content |> Js.String.trim);

let parseDirectMessage = parsePrefixedMessage("~?");

let parseChannelMessage = parsePrefixedMessage("~");

let parseMessage (msg) =
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

let logMessage (msg) = {
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
  Js.log(channelName ++ ": " ++ fullUsername ++ "> " ++ content)
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
  (Negative, "Very doubtful")
|];

let handleMessage (msg) = {
  logMessage(msg);
  parseMessage(msg)
  |> Option.iter(
       (command) =>
         switch (command) {
         | Help =>
           Js.log("help from " ++ User.username(Message.author(msg)));
           let _ = msg |> Message.reply("~roll d20 + 4d10 - 2d6 + 3dF + 5");
           ()
         | Ping =>
           Js.log("ping from " ++ User.username(Message.author(msg)));
           let _ = msg |> Message.reply("pong");
           ()
         | Roll(data) =>
           State.UserState.update(
             Message.author(msg),
             (state) => {...state, rolls: state.rolls + 1}
           );
           Js.log(
             "roll from "
             ++ User.username(Message.author(msg))
             ++ " "
             ++ Roller.stringify(data)
           );
           let rolls = Roller.roll(data, engine);
           let _ =
             msg
             |> Message.reply(
                  :split SplitOptions.make(),
                  Roller.emojify(data, rolls)
                  ++ " = "
                  ++ Js.String.make(Roller.calculateTotal(data, rolls))
                );
           ()
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
                  )
                );
           ()
         | Get =>
           let state = State.UserState.get(Message.author(msg));
           let _ = msg |> Message.reply(state.note);
           ()
         | Set(note) =>
           State.UserState.update(
             Message.author(msg),
             (state) => {...state, note}
           );
           let _ = msg |> Message.reply("note = " ++ note);
           ()
         }
     )
};

client
|> Client.onReady(
     () => {
       client
       |> Client.user
       |> Option.orRaise(Failure("expected a user"))
       |> ClientUser.setPresence(:game "~help")
       |> promiseMap((stuff) => Js.log(stuff))
       |> promiseEnd;
       Js.log("Bot is ready!")
     }
   );

client |> Client.onMessage(handleMessage);

client |> Client.login(Node.Fs.readFileAsUtf8Sync("./token.txt") |> Js.String.trim);

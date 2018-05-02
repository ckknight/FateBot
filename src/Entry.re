open Discord;

open Utils;

let client = Client.make();

type role =
  | Admin
  | Normie
  | Bot;

let role_of_user = user =>
  if (user |> User.bot) {
    Bot;
  } else {
    switch (user |> User.username) {
    | "ckknight" => Admin
    | _ => Normie
    };
  };

let parseMessage = msg =>
  switch (msg |> Message.author |> role_of_user) {
  | Bot => None
  | _ => Command.parseMessage(msg)
  };

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

let handleMessage = msg => {
  logMessage(msg);
  parseMessage(msg)
  |> Belt.Option.mapWithDefault(_, (), Command.handleMessage(msg));
};

client
|> Client.onError(exn =>
     switch (Utils.exnCode(exn)) {
     | Some("ECONNRESET") => Js.log("Connection reset")
     | _ => Js.log(exn)
     }
   );

client
|> Client.onReady(() => {
     client
     |> Client.user
     |> Belt.Option.getExn
     |> ClientUser.setPresence(~game="~help")
     |> promiseMap(stuff => Js.log(stuff))
     |> promiseEnd;
     Js.log("Bot is ready!");
   });

client |> Client.onMessage(handleMessage);

let token = Node.Fs.readFileAsUtf8Sync("./token.txt") |> Js.String.trim;

client |> Client.login(token);
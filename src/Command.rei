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

let parseMessage: (Discord.client, Discord.message) => option(t);

let handleMessage: (Discord.message, t) => unit;
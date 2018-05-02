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

let handle = (engine, msg) => {
  let (mood, text) =
    Random.pick(eightBallResults, engine) |> Belt.Option.getExn;
  let _ =
    msg
    |> Discord.Message.reply(
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
};
open Utils;

type token =
  | Operator(string)
  | Dice(int, int, int)
  | Constant(int);

type t = array(token);

let getMatchLength (match_) = Js.String.length(match_[0]);

let diceExpMatcher (str) =
  str
  |> Js.String.match_(
       Js.Re.fromString(
         "^([1-9][0-9]*)?(?:d|D)((?:([1-9][0-9]*)(?:\\.\\.([1-9][0-9]*))?)|\\%|f|F)"
       )
     )
  |> Option.map(
       (match_) => {
         let diceCount = parseInt(1, match_[1]);
         let dice =
           switch (match_[2] |> Js.String.toLowerCase) {
           | "%" => Dice(diceCount, 1, 100)
           | "f" => Dice(diceCount, (-1), 1)
           | _ =>
             if (truthy(match_[4])) {
               Dice(diceCount, parseInt(1, match_[3]), parseInt(1, match_[4]))
             } else {
               Dice(diceCount, 1, parseInt(6, match_[3]))
             }
           };
         ([dice], getMatchLength(match_))
       }
     );

let constantMatcher (str) =
  str
  |> Js.String.match_(Js.Re.fromString("^([1-9][0-9]*)"))
  |> Option.map(
       (match_) => {
         let value = parseInt(0, match_[1]);
         ([Constant(value)], getMatchLength(match_))
       }
     );

let spaceMatcher (str) =
  str
  |> Js.String.match_(Js.Re.fromString("^\\s*"))
  |> Option.map((match_) => ([], getMatchLength(match_)));

let orCombinator = Option.orElse;

let andCombinator (f, g, str) =
  f(str)
  |> Option.bind(
       ((tokens, index)) =>
         g(Js.String.substringToEnd(:from index, str))
         |> Option.map(
              ((newTokens, newIndex)) => (tokens @ newTokens, index + newIndex)
            )
     );

let andMaybeCombinator (f, g, str) =
  f(str)
  |> Option.map(
       (x) => {
         let (tokens, index) = x;
         switch (g(Js.String.substringToEnd(:from index, str))) {
         | None => x
         | Some((newTokens, newIndex)) => (
             tokens @ newTokens,
             index + newIndex
           )
         }
       }
     );

let manyCombinator (f) = {
  let rec g (str) = andMaybeCombinator(f, g, str);
  g
};

let operatorMatcher (str) =
  switch (str |> Js.String.match_(Js.Re.fromString("^[+-]"))) {
  | None => None
  | Some(match_) => Some(([Operator(match_[0])], getMatchLength(match_)))
  };

let diceOrConstantMatcher =
  andCombinator(spaceMatcher, orCombinator(diceExpMatcher, constantMatcher));

let spacedOperatorMatcher = andCombinator(spaceMatcher, operatorMatcher);

let finalCombinator =
  andMaybeCombinator(
    diceOrConstantMatcher,
    manyCombinator(andCombinator(spacedOperatorMatcher, diceOrConstantMatcher))
  );

let parseRoll (exp) =
  finalCombinator(exp)
  |> Option.bind(
       ((tokens, index)) =>
         if (index === Js.String.length(exp)) {
           Some(Array.of_list(tokens))
         } else {
           None
         }
     );

let stringifyRaw (f, tokens: t) =
  tokens |> Js.Array.map(f) |> Js.Array.joinWith(" ");

let stringify =
  stringifyRaw(
    (token) =>
      switch (token) {
      | Operator(op) => op
      | Dice(count, min, max) =>
        if (min === (-1) && max === 1) {
          Js.Int.toString(count) ++ "dF"
        } else if (min === 1) {
          Js.Int.toString(count) ++ "d" ++ Js.Int.toString(max)
        } else {
          Js.Int.toString(count)
          ++ "r"
          ++ Js.Int.toString(min)
          ++ ".."
          ++ Js.Int.toString(max)
        }
      | Constant(value) => Js.Int.toString(value)
      }
  );

let roll (tokens: t, engine: Random.t) =
  tokens
  |> Js.Array.map(
       (token) =>
         switch (token) {
         | Dice(count, min, max) =>
           arrayRange(count)
           |> Js.Array.map(
                (_) => {
                  Js.log3("Oh shit dawg", min, max);
                  Random.int(min, max, engine)
                }
              )
         | _ => [||]
         }
     );

let eval
    (
      tokens: array(token),
      rolls: array(array(int)),
      state: 's,
      onOperator: (string, 's) => 's,
      onConstant: (int, 's) => 's,
      onDice: (int, int, array(int), 's) => 's
    )
    : 's =
  arrayZip(tokens, rolls)
  |> Js.Array.reduce(
       (state, (token, rollArray)) =>
         switch (token) {
         | Operator(op) => onOperator(op, state)
         | Constant(value) => onConstant(value, state)
         | Dice(_, min, max) => onDice(min, max, rollArray, state)
         },
       state
     );

let calculateTotal (tokens: t, rolls: array(array(int))) : int = {
  let operate (value, (adding, total)) = (
    adding,
    if (adding) {
      total + value
    } else {
      total - value
    }
  );
  let sum = Js.Array.reduce((+), 0);
  eval(
    tokens,
    rolls,
    (true, 0),
    (op) =>
      switch (op) {
      | "+" => (((_, total)) => (true, total))
      | "-" => (((_, total)) => (false, total))
      | _ => ((x) => x)
      },
    operate,
    (_min, _max, rollArray) => operate(sum(rollArray))
  )
  |> (((_adding, total)) => total)
};

let emojifyFateDie (roll: int) =
  if (roll < 0) {
    {j|⊟|j}
  } else if (roll > 0) {
    {j|⊞|j}
  } else {
    {j|⊡|j}
  };

let emojifyNumeralDie (roll: int) =
  switch (roll) {
  | 0 => ":zero:"
  | 1 => ":one:"
  | 2 => ":two:"
  | 3 => ":three:"
  | 4 => ":four:"
  | 5 => ":five:"
  | 6 => ":six:"
  | 7 => ":seven:"
  | 8 => ":eight:"
  | 9 => ":nine:"
  | 10 => ":keycap_ten:"
  | x => Js.String.make(x)
  };

let emojifyPercentageDie (roll: int) =
  switch (roll) {
  | 100 => ":100:"
  | _ => emojifyNumeralDie(roll / 10) ++ emojifyNumeralDie(roll mod 10)
  };

let emojifyPermillageDie (roll: int) =
  emojifyNumeralDie(roll / 100)
  ++ emojifyNumeralDie(roll / 10 mod 10)
  ++ emojifyNumeralDie(roll mod 10);

let emojifyD20Die (roll: int) = Js.String.make(roll);

/* "231440119876288512" */
let emojify (tokens: t, rolls: array(array(int))) : string =
  eval(
    tokens,
    rolls,
    "",
    (op, acc) => acc ++ " " ++ op ++ " ",
    (value, acc) => acc ++ Js.String.make(value),
    (min, max, rolls, acc) =>
      acc
      ++ (
        rolls
        |> Js.Array.map(
             if (min === (-1) && max === 1) {
               emojifyFateDie
             } else if (min === 1 && max <= 10) {
               emojifyNumeralDie
             } else if (min === 1 && max == 20) {
               emojifyD20Die
             } else if (min === 1 && max == 100) {
               emojifyPercentageDie
             } else if (min === 1 && max == 1000) {
               emojifyPermillageDie
             } else {
               Js.String.make
             }
           )
        |> (
          (array) => {
            let inner = Js.Array.joinWith(" + ", array);
            switch (array |> Js.Array.length) {
            | 1 => inner
            | _ => {j|(|j} ++ inner ++ {j|)|j}
            }
          }
        )
      )
  );

let getAll () : Js.Dict.t('a) =
  (
    try (Node.Fs.readFileAsUtf8Sync("./state.json")) {
    | Js.Exn.Error(e) as exn =>
      e
      |> Utils.exnCode
      |> Utils.Option.filter((code) => code === "ENOENT")
      |> Utils.Option.mapTo("")
      |> Utils.Option.orRaise(exn)
    }
  )
  |> (
    (content) =>
      try (Js.Json.parseExn(content)) {
      | _ => Js.Json.parseExn("{}")
      }
  )
  |> Js.Json.classify
  |> (
    (json) =>
      switch (json) {
      | Js.Json.JSONObject(dict) => Some(dict)
      | _ => None
      }
  )
  |> Utils.Option.value(Js.Dict.empty());

let getAll = getAll |> Utils.memoize;

let getForSnowflake (snowflake: Discord.snowflake) : option(Js.Json.t) =
  Js.Dict.get(getAll(), Discord.Snowflake.toString(snowflake));

let unsafeDeleteKey: (Js.Dict.t('a), string) => unit = [%bs.raw
  {|function(a,b){return(delete a[b],0)}|}
];

let setForSnowflake (snowflake: Discord.snowflake, value: 'a) = {
  let state = getAll();
  let key = Discord.Snowflake.toString(snowflake);
  value
  |> Js.Json.stringifyAny
  |> (
    (stringifiedValue) =>
      switch (stringifiedValue) {
      | None => unsafeDeleteKey(state, key)
      | Some(stringifiedValue) =>
        Js.Dict.set(state, key, stringifiedValue |> Js.Json.parseExn)
      }
  );
  state
  |> Js.Json.object_
  |> Js.Json.stringify
  |> Node.Fs.writeFileAsUtf8Sync("./state.json")
};

module StateAccessor
       (
         T: {
           type t;
           type state;
           let encode: state => Js.Json.t;
           let decode: option(Js.Json.t) => state;
           let getSnowflake: t => Discord.Snowflake.t;
         }
       ) = {
  let get (t) = t |> T.getSnowflake |> getForSnowflake |> T.decode;
  let set (t, state) = setForSnowflake(t |> T.getSnowflake, state |> T.encode);
  let update (t, updater) = set(t, updater(get(t)));
};

module UserState = {
  type t = {
    note: string,
    rolls: int
  };
  include
    StateAccessor(
      {
        type state = t;
        type t = Discord.User.t;
        let getSnowflake = Discord.User.id;
        let encode (userState) =
          [|
            ("note", userState.note |> Js.Json.string),
            ("rolls", userState.rolls |> float_of_int |> Js.Json.number)
          |]
          |> Js.Dict.fromArray
          |> Js.Json.object_;
        let decode (userState) =
          userState
          |> Utils.Option.bind(Js.Json.decodeObject)
          |> Utils.Option.value(Js.Dict.empty())
          |> (
            (dict) => {
              note:
                Js.Dict.get(dict, "note")
                |> Utils.Option.bind(Js.Json.decodeString)
                |> Utils.Option.value(""),
              rolls:
                Js.Dict.get(dict, "rolls")
                |> Utils.Option.bind(Js.Json.decodeNumber)
                |> Utils.Option.value(0.0)
                |> int_of_float
            }
          );
      }
    );
};

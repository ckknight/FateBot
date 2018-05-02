let parseInt = (defaultValue, str) => {
  let value = Js.Float.fromString(str);
  if (Js.Float.isNaN(value)) {
    defaultValue;
  } else {
    int_of_float(value);
  };
};

/* let truthy (value: 'a) : bool = Obj.magic(value) ? true : false; */
[@bs.val] external truthy : 'a => bool = "Boolean";

let promiseMap = f => Js.Promise.then_(x => Js.Promise.resolve(f(x)));

let promiseEnd = promise => {
  let _ =
    Js.Promise.catch(
      error => {
        Js.log(error);
        Js.Promise.resolve();
      },
      promise,
    );
  ();
};

[@bs.get] external exnCode : Js.Exn.t => Js.Undefined.t(string) = "code";

let exnCode = exn => Js.Undefined.toOption(exnCode(exn));

let parseJson = data =>
  try (Some(Js.Json.parseExn(data))) {
  | _ => None
  };

let memoize = fn => {
  let cache = ref(None);
  arg =>
    switch (cache.contents) {
    | None =>
      let result = fn(arg);
      cache := Some(result);
      result;
    | Some(x) => x
    };
};

let magicAsArray = (item: 'a) : array('a) =>
  if (Js.Array.isArray(item)) {
    Obj.magic(item);
  } else {
    [|item|];
  };
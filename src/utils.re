module Option = {
  type t('a) = option('a);
  let some (value) = Some(value);
  let isSome (option) =
    switch (option) {
    | None => false
    | Some(_) => true
    };
  let isNone (option) =
    switch (option) {
    | None => true
    | Some(_) => false
    };
  let bind (f, option) =
    switch (option) {
    | None => None
    | Some(x) => f(x)
    };
  let equal (eq, a, b) =
    switch (a) {
    | None => isNone(b)
    | Some(x) =>
      switch (b) {
      | None => false
      | Some(y) => eq(x, y)
      }
    };
  let map (f) = bind((x) => Some(f(x)));
  let mapTo (x) = map((_) => x);
  let iter (f, option) =
    switch (option) {
    | None => ()
    | Some(x) => f(x)
    };
  let value (default, option) =
    switch (option) {
    | None => default
    | Some(x) => x
    };
  let valueMap (default, f, option) =
    switch (option) {
    | None => default
    | Some(x) => f(x)
    };
  let filter (f) =
    bind(
      (x) =>
        if (f(x)) {
          Some(x)
        } else {
          None
        }
    );
  let both (x, y) = x |> bind((a) => y |> map((b) => (a, b)));
  let map2 (f, x, y) = both(x, y) |> map(((a, b)) => f(a, b));
  let orElse (f, g, x) =
    switch (f(x)) {
    | None => g(x)
    | Some(_) as t => t
    };
  let orRaise (exn, option) =
    switch (option) {
    | None => raise(exn)
    | Some(x) => x
    };
  let firstSome (x, y) =
    switch (x) {
    | None => y
    | Some(_) as t => t
    };
  let someIf (condition, x) =
    if (condition) {
      Some(x)
    } else {
      None
    };
  let orDefault (f, option) =
    switch (option) {
    | None => f()
    | Some(x) => x
    };
  module Infix = {
    let (>>=) (option, f) = bind(f, option);
    let (||>) (option, f) = map(f, option);
  };
};

let parseInt (defaultValue, str) = {
  let value = Js.Float.fromString(str);
  if (Js.Float.isNaN(value)) {
    defaultValue
  } else {
    int_of_float(value)
  }
};

let arrayRange (count) = {
  let array: array(int) = [||];
  for (x in 0 to count - 1) {
    let _ = Js.Array.push(x, array);
    ()
  };
  array
};

let arrayZip (x: array('a), y: array('b)) : array(('a, 'b)) =
  x |> Js.Array.mapi((value, index) => (value, y[index]));

/* let truthy (value: 'a) : bool = Obj.magic(value) ? true : false; */
[@bs.val] external truthy : 'a => bool = "Boolean";

let promiseMap (f) = Js.Promise.then_((x) => Js.Promise.resolve(f(x)));

let promiseEnd (promise) = {
  let _ =
    Js.Promise.catch(
      (error) => {
        Js.log(error);
        Js.Promise.resolve()
      },
      promise
    );
  ()
};

[@bs.get] external exnCode : Js.Exn.t => Js.Undefined.t(string) = "code";

let exnCode (exn) = Js.Undefined.to_opt(exnCode(exn));

let parseJson (data) =
  try (Some(Js.Json.parseExn(data))) {
  | _ => None
  };

let memoize (fn) = {
  let cache = ref(None);
  (arg) =>
    switch (cache.contents) {
    | None =>
      let result = fn(arg);
      cache := Some(result);
      result
    | Some(x) => x
    }
};

let magicAsArray (item: 'a) : array('a) =
  if (Js.Array.isArray(item)) {
    Obj.magic(item)
  } else {
    [|item|]
  };

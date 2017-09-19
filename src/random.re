type t;

[@bs.module "random-js"] [@bs.scope "engines"] external nativeMath : t = "";

[@bs.module "random-js"] [@bs.scope "engines"]
external browserCrypto : Js.null((unit => t)) =
  "";

module MersenneTwister = {
  type mt;
  [@bs.module "random-js"] [@bs.scope "engines"] external make : unit => mt =
    "mt19937";
  external engine : mt => t = "%identity";
  [@bs.send.pipe : mt] external seed : int => mt = "";
  [@bs.send.pipe : mt] external seedWithArray : array(int) => mt = "";
  [@bs.send] external autoSeed : mt => mt = "";
  [@bs.send.pipe : mt] external discard : int => mt = "";
  [@bs.send] external getUseCount : mt => int = "";
};

type make('a) = [@bs] (t => 'a);

[@bs.module "random-js"] external generateEntropyArray : unit => array(int) =
  "";

/* [-0x80000000, 0x7fffffff] */
[@bs.module "random-js"] external int32 : t => int = "";

/* [0, 0xffffffff] */
[@bs.module "random-js"] external uint32 : t => float = "";

/* [0, 0x1fffffffffffff] */
[@bs.module "random-js"] external uint53 : t => float = "";

/* [0, 0x20000000000000] */
[@bs.module "random-js"] external uint53Full : t => float = "";

/* [-0x20000000000000, 0x1fffffffffffff] */
[@bs.module "random-js"] external int53 : t => float = "";

/* [-0x20000000000000, 0x20000000000000] */
[@bs.module "random-js"] external int53Full : t => float = "";

/* [min, max] */
[@bs.module "random-js"] external integer : (float, float) => make(float) = "";

let int (min, max) = {
  let makeFloat = integer(float_of_int(min), float_of_int(max));
  (t) => int_of_float([@bs] makeFloat(t))
};

let integer (min, max) = {
  let makeFloat = integer(min, max);
  (t) => [@bs] makeFloat(t)
};

/* [0, 1] (floating point) */
[@bs.module "random-js"] external realZeroToOneInclusive : t => float = "";

/* [0, 1) (floating point) */
[@bs.module "random-js"] external realZeroToOneExclusive : t => float = "";

/*
 * [left, right) (floating-point)
 * or
 * [left, right] (floating-point)
 */
[@bs.module "random-js"]
external real : (float, float, Js.boolean) => make(float) =
  "";

let real (:inclusive=false, min, max) = {
  let makeFloat = real(min, max, inclusive |> Js.Boolean.to_js_boolean);
  (t) => [@bs] makeFloat(t)
};

/* 50% likelihood of true vs false */
[@bs.module "random-js"] external bool : unit => make(Js.boolean) = "";

let bool = {
  let makeBool = bool();
  (t) => Js.to_bool([@bs] makeBool(t))
};

/* probably * 100% likelihood of true */
[@bs.module "random-js"]
external boolByProbability : float => make(Js.boolean) =
  "bool";

let boolByProbability (probability) = {
  let makeBool = boolByProbability(probability);
  (t) => Js.to_bool([@bs] makeBool(t))
};

/* numerator / denominator * 100% likelihood of true */
[@bs.module "random-js"]
external boolByFraction : (float, float) => make(Js.boolean) =
  "bool";

let boolByFraction (numerator, denominator) = {
  let makeBool = boolByFraction(numerator, denominator);
  (t) => Js.to_bool([@bs] makeBool(t))
};

[@bs.module "random-js"]
external pick :
  (t, array('a), Js.undefined(int), Js.undefined(int)) => Js.undefined('a) =
  "";

let pick (:start=?, :finish=?, array: array('a), engine: t) : option('a) =
  pick(
    engine,
    array,
    start |> Js.Undefined.from_opt,
    finish |> Js.Undefined.from_opt
  )
  |> Js.Undefined.to_opt;

[@bs.module "random-js"]
external picker :
  (array('a), Js.undefined(int), Js.undefined(int)) => make(Js.undefined('a)) =
  "";

let picker (:start=?, :finish=?, array) = {
  let makePick =
    picker(
      array,
      start |> Js.Undefined.from_opt,
      finish |> Js.Undefined.from_opt
    );
  (t) => [@bs] makePick(t) |> Js.Undefined.to_opt
};

[@bs.module "random-js"] external shuffle : (t, array('a), int) => array('a) =
  "";

let shuffleInPlace (:downTo=0, array, t) = shuffle(t, array, downTo);

let shuffle (:downTo=0, array, t) = shuffle(t, Js.Array.copy(array), downTo);

[@bs.module "random-js"] external sample : (t, array('a), int) => array('a) =
  "";

let sample (population, sampleSize, t) = sample(t, population, sampleSize);

[@bs.module "random-js"] external die : int => make(int) = "";

let die (sideCount) = {
  let makeInt = die(sideCount);
  (t) => [@bs] makeInt(t)
};

[@bs.module "random-js"] external dice : (int, int) => make(array(int)) = "";

let dice (sideCount, dieCount) = {
  let makeIntArray = dice(sideCount, dieCount);
  (t) => [@bs] makeIntArray(t)
};

[@bs.module "random-js"] external uuid4 : t => string = "";

type make_string_of_length = [@bs] ((t, int) => string);

[@bs.module "random-js"] external string : unit => make_string_of_length =
  "string";

let string = {
  let makeString = string();
  (length, t) => [@bs] makeString(t, length)
};

[@bs.module "random-js"]
external stringOfPool : string => make_string_of_length =
  "string";

let stringOfPool (pool) = {
  let makeString = stringOfPool(pool);
  (length, t) => [@bs] makeString(t, length)
};

[@bs.module "random-js"] external hex : Js.boolean => make_string_of_length =
  "";

let hex (uppercase) = {
  let makeString = hex(uppercase |> Js.Boolean.to_js_boolean);
  (length, t) => [@bs] makeString(t, length)
};

[@bs.module "random-js"]
external date : (Js.Date.t, Js.Date.t) => make(Js.Date.t) =
  "";

let date (min, max) = {
  let makeDate = date(min, max);
  (t) => [@bs] makeDate(t)
};

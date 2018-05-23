type t;

type position = (int, int);

type direction =
  | North
  | East
  | South
  | West;

type color =
  | White
  | Black;

type stoneType =
  | FlatStone
  | StandingStone
  | Capstone;

type leftStones;

type action =
  | Place(stoneType, position)
  | Move(position, direction, leftStones);

let create: int => t;

let boardSize: t => int;

let position: (int, int) => position;

let place: (stoneType, position, t) => Belt.Result.t(t, string);

let leftStones: list(int) => leftStones;

let move: (position, direction, leftStones, t) => Belt.Result.t(t, string);

let pieces: (position, t) => list((color, stoneType));

let whoseTurn: t => option(color);

let dispatch: (action, t) => Belt.Result.t(t, string);

let actions: t => list(action);
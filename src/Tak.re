open Belt;

type color =
  | White
  | Black;

type status =
  | WhiteInitial
  | BlackInitial
  | WhiteTurn
  | BlackTurn
  | WhiteWin
  | BlackWin;

type position = (int, int);

let position = (x, y) : position => (x, y);

type direction =
  | North
  | East
  | South
  | West;

type stoneType =
  | FlatStone
  | StandingStone
  | Capstone;

type stone = (color, stoneType);

let positionToIndex = (boardSize, (x, y)) => y * boardSize + x;

type pieces = Map.Int.t(list(stone));

type leftStones = list(int);

type action =
  | Place(stoneType, position)
  | Move(position, direction, leftStones);

type board = {
  boardSize: int,
  whitePiecesRemaining: int,
  blackPiecesRemaining: int,
  whiteCapstonesRemaining: int,
  blackCapstonesRemaining: int,
  status,
  pieces,
  actions: list(action),
};

type t = board;

let getStonesByPosition = (position, board) =>
  Map.Int.getWithDefault(
    board.pieces,
    positionToIndex(board.boardSize, position),
    [],
  );

let getTopStoneByPosition = (position, board) =>
  switch (getStonesByPosition(position, board)) {
  | [stone, ..._] => Some(stone)
  | _ => None
  };

let addStoneToPosition = (stone, position, board) =>
  Map.Int.updateU(
    board.pieces,
    positionToIndex(board.boardSize, position),
    (. stones) => {
      let stones = Option.getWithDefault(stones, []);
      Some([stone, ...stones]);
    },
  );

let piecesRemainingByBoardSize = boardSize =>
  switch (boardSize) {
  | 3 => Some((10, 0))
  | 4 => Some((15, 0))
  | 5 => Some((21, 1))
  | 6 => Some((30, 1))
  | 7 => Some((40, 2)) /* TODO: support 1 or 2 */
  | 8 => Some((50, 2))
  | _ => None
  };

let create = boardSize =>
  switch (piecesRemainingByBoardSize(boardSize)) {
  | Some((piecesRemaining, capstonesRemaining)) => {
      boardSize,
      whitePiecesRemaining: piecesRemaining,
      blackPiecesRemaining: piecesRemaining,
      whiteCapstonesRemaining: capstonesRemaining,
      blackCapstonesRemaining: capstonesRemaining,
      status: WhiteInitial,
      pieces: Map.Int.empty,
      actions: [],
    }
  | _ => failwith("Unacceptable boardSize " ++ string_of_int(boardSize))
  };

let boardSize = board => board.boardSize;

let canPlace = board =>
  switch (board.status) {
  | BlackWin
  | WhiteWin => false
  | _ => true
  };

let attemptToPlace = board =>
  switch (board.status) {
  | BlackWin => Result.Error("Black has already won")
  | WhiteWin => Result.Error("White has already won")
  | _ => Result.Ok()
  };

let whoseTurn = board =>
  switch (board.status) {
  | BlackInitial
  | BlackTurn => Some(Black)
  | WhiteInitial
  | WhiteTurn => Some(White)
  | _ => None
  };

let isPositionTaken = (position, board) =>
  ! Js.List.isEmpty(getStonesByPosition(position, board));

let attemptPositionTaken = (position, board) =>
  if (isPositionTaken(position, board)) {
    Result.Error("position is already taken");
  } else {
    Result.Ok();
  };

let isPositionWithinBounds = ((x, y), {boardSize}) =>
  x >= 0 && x < boardSize && y >= 0 && y < boardSize;

let attemptPositionWithinBounds = (position, board) =>
  if (isPositionWithinBounds(position, board)) {
    Result.Ok();
  } else {
    Result.Error("position not within bounds");
  };

let range = size => List.makeByU(size, (. index) => index);

let applyDirection = ((x, y), direction) =>
  switch (direction) {
  | North => (x, y - 1)
  | East => (x + 1, y)
  | South => (x, y + 1)
  | West => (x - 1, y)
  };

let isRoad = stoneType =>
  switch (stoneType) {
  | FlatStone
  | Capstone => true
  | _ => false
  };

let hasRoad = (color, initialPosition, isEnd, board) => {
  let connections = MutableSet.Int.make();
  let rec aux = position =>
    if (! isPositionWithinBounds(position, board)) {
      false;
    } else {
      switch (getTopStoneByPosition(position, board)) {
      | Some((stoneColor, stoneType))
          when stoneColor == color && isRoad(stoneType) =>
        let added =
          MutableSet.Int.addCheck(
            connections,
            positionToIndex(board.boardSize, position),
          );
        if (! added) {
          false;
        } else {
          isEnd(position)
          || [North, East, South, West]
          |> List.someU(_, (. direction) =>
               aux(applyDirection(position, direction))
             );
        };
      | _ => false
      };
    };
  aux(initialPosition);
};

let hasHorizontalRoad = (color, row, board) =>
  hasRoad(
    color,
    (0, row),
    ((column, _)) => column >= board.boardSize - 1,
    board,
  );

let hasVerticalRoad = (color, column, board) =>
  hasRoad(
    color,
    (column, 0),
    ((_, row)) => row >= board.boardSize - 1,
    board,
  );

let calculateRoads = (color, board) =>
  range(board.boardSize)
  |> List.someU(_, (. index) =>
       hasHorizontalRoad(color, index, board)
       || hasVerticalRoad(color, index, board)
     );

let checkForWinner = (turnColor, board) => {
  let roads =
    [White, Black]
    |> List.keepMapU(_, (. color) =>
         calculateRoads(color, board) ? Some(color) : None
       );
  let roadWinner =
    switch (roads) {
    | [winnerColor] => Some(winnerColor)
    | [_, _] => Some(turnColor)
    | _ => None
    };
  switch (roadWinner) {
  | Some(winnerColor) => {
      ...board,
      status: winnerColor == Black ? BlackWin : WhiteWin,
    }
  | _ => board
  };
};

let doPlace = (stoneType, position, board) =>
  attemptToPlace(board)
  |> Result.flatMapU(_, (. _) =>
       attemptPositionWithinBounds(position, board)
     )
  |> Result.flatMapU(_, (. _) => attemptPositionTaken(position, board))
  |> Result.flatMapU(
       _,
       (. _) => {
         let (stoneColor, initial) =
           switch (board.status) {
           | BlackInitial => (White, true)
           | WhiteInitial => (Black, true)
           | BlackTurn => (Black, false)
           | WhiteTurn => (White, false)
           | _ => failwith("Unexpected board.status")
           };
         if (initial && stoneType != FlatStone) {
           Result.Error("a FlatStone must be placed initially");
         } else {
           let {
             whiteCapstonesRemaining,
             blackCapstonesRemaining,
             whitePiecesRemaining,
             blackPiecesRemaining,
           } = board;
           let (
             whiteCapstonesRemaining,
             blackCapstonesRemaining,
             whitePiecesRemaining,
             blackPiecesRemaining,
           ) =
             switch (stoneColor, stoneType) {
             | (White, Capstone) => (
                 whiteCapstonesRemaining - 1,
                 blackCapstonesRemaining,
                 whitePiecesRemaining,
                 blackPiecesRemaining,
               )
             | (Black, Capstone) => (
                 whiteCapstonesRemaining,
                 blackCapstonesRemaining - 1,
                 whitePiecesRemaining,
                 blackPiecesRemaining,
               )
             | (White, _) => (
                 whiteCapstonesRemaining,
                 blackCapstonesRemaining,
                 whitePiecesRemaining - 1,
                 blackPiecesRemaining,
               )
             | (Black, _) => (
                 whiteCapstonesRemaining,
                 blackCapstonesRemaining,
                 whitePiecesRemaining,
                 blackPiecesRemaining - 1,
               )
             };
           Result.Ok(
             {
               ...board,
               whiteCapstonesRemaining,
               blackCapstonesRemaining,
               whitePiecesRemaining,
               blackPiecesRemaining,
               status:
                 switch (board.status) {
                 | BlackInitial
                 | BlackTurn => WhiteTurn
                 | WhiteInitial => BlackInitial
                 | WhiteTurn => BlackTurn
                 | _ => failwith("Unexpected board.status")
                 },
               pieces:
                 addStoneToPosition(
                   (stoneColor, stoneType),
                   position,
                   board,
                 ),
             }
             |> checkForWinner(whoseTurn(board) |> Option.getExn),
           );
         };
       },
     );

let canMove = board =>
  switch (board.status) {
  | BlackTurn
  | WhiteTurn => true
  | _ => false
  };

let attemptMove = board =>
  switch (board.status) {
  | BlackTurn
  | WhiteTurn => Result.Ok()
  | WhiteInitial
  | BlackInitial => Result.Error("cannot move in the initial turns")
  | WhiteWin
  | BlackWin => Result.Error("game has already been won")
  };

let leftStones = input => {
  let rec leftStonesAux = (input, isFirst) =>
    switch (input) {
    | [value, ...rest] =>
      if (value < 1 && ! (value == 0 && isFirst)) {
        failwith("Expected at least 1, or 0 on the first");
      } else {
        leftStonesAux(rest, false);
      }
    | [] =>
      if (isFirst) {
        failwith("Expected at least one item in list");
      } else {
        ();
      }
    };
  leftStonesAux(input, true);
  input;
};

let movePieces = (stones, position, direction, leftStones, board) => {
  let rec aux = (stonesInHand, position, leftStones, board) =>
    switch (leftStones, stonesInHand) {
    | ([], []) => Some(board.pieces)
    | ([], _)
    | (_, []) => None
    | (
        [toLeave, ...restLeftStones],
        [(_, handStoneType), ...restStonesInHand],
      ) =>
      if (! isPositionWithinBounds(position, board)) {
        None;
      } else {
        let stopped =
          switch (getTopStoneByPosition(position, board)) {
          | Some((_, stoneType)) =>
            switch (stoneType) {
            | FlatStone => false
            | StandingStone =>
              ! Js.List.isEmpty(restStonesInHand) || handStoneType != Capstone
            | _ => true
            }
          | _ => false
          };
        if (stopped) {
          None;
        } else {
          List.splitAt(stonesInHand, toLeave)
          |> Option.flatMapU(_, (. (stonesToLeave, stonesToKeep)) =>
               aux(
                 stonesToKeep,
                 applyDirection(position, direction),
                 restLeftStones,
                 {
                   ...board,
                   pieces:
                     Map.Int.updateU(
                       board.pieces,
                       positionToIndex(board.boardSize, position),
                       (. currentStones) =>
                       Some(
                         List.reverseConcat(
                           stonesToLeave,
                           List.mapU(
                             Option.getWithDefault(currentStones, []),
                             (. stone) =>
                             switch (stone) {
                             | (color, StandingStone) => (color, FlatStone)
                             | stone => stone
                             }
                           ),
                         ),
                       )
                     ),
                 },
               )
             );
        };
      }
    };
  aux(
    List.reverse(stones),
    position,
    leftStones,
    {
      ...board,
      pieces:
        Map.Int.remove(
          board.pieces,
          positionToIndex(board.boardSize, position),
        ),
    },
  );
};

let doMove = (position, direction, leftStones, board) =>
  attemptMove(board)
  |> Result.flatMapU(
       _,
       (. _) => {
         let stones = getStonesByPosition(position, board);
         switch (stones, whoseTurn(board)) {
         | ([(color, _), ..._], Some(playerColor))
             when color == playerColor =>
           switch (movePieces(stones, position, direction, leftStones, board)) {
           | Some(pieces) =>
             Result.Ok(
               {
                 ...board,
                 status:
                   switch (board.status) {
                   | BlackTurn => WhiteTurn
                   | WhiteTurn => BlackTurn
                   | _ => failwith("Unexpected board.status")
                   },
                 pieces,
               }
               |> checkForWinner(playerColor),
             )
           | _ => Result.Error("cannot move there")
           }
         | _ => Result.Error("Not the correct player")
         };
       },
     );

let pieces = getStonesByPosition;

let dispatch = (action, board) =>
  (
    switch (action) {
    | Place(stoneType, position) => doPlace(stoneType, position, board)
    | Move(position, direction, leftStones) =>
      doMove(position, direction, leftStones, board)
    }
  )
  |> Result.mapU(_, (. board) =>
       {...board, actions: [action, ...board.actions]}
     );

let actions = board => board.actions;

let place = (stoneType, position, board) =>
  dispatch(Place(stoneType, position), board);

let move = (position, direction, leftStones, board) =>
  dispatch(Move(position, direction, leftStones), board);

type thing = {
  alpha: int,
  bravo: float,
  charlie: int,
  delta: int,
  echo: int,
  foxtrot: int,
};

let x = {alpha: 1, bravo: 2., charlie: 3, delta: 5, echo: 6, foxtrot: 7};
type client;

type singleResponse = Js.t({. data: Js.t({. url: string})});

type multipleResponse = Js.t({. data: array(Js.t({. url: string}))});

[@bs.module] external makeClient : unit => client = "giphy-api";

[@bs.send.pipe : client]
external search : Js.t({. q: string}) => Js.Promise.t(multipleResponse) =
  "";

let search (query, client) = search({"q": query}, client);

let getRandomUrl (searchResults, engine) =
  switch (Random.pick(searchResults##data, engine)) {
  | Some(x) => x##url
  | None => ""
  };

[@bs.send.pipe : client]
external random : string => Js.Promise.t(singleResponse) =
  "";

let random (tag, client) =
  random(tag, client)
  |> Js.Promise.then_((response) => Js.Promise.resolve(response##data##url));

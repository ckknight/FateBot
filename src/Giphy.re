type client;

type singleResponse = {. "data": {. "url": string}};

type multipleResponse = {. "data": array({. "url": string})};

[@bs.module] external makeClient : unit => client = "giphy-api";

[@bs.send.pipe: client]
external search : {. "q": string} => Js.Promise.t(multipleResponse) = "";

let search = (query, client) => search({"q": query}, client);

let getRandomUrl = (searchResults, engine) =>
  switch (Random.pick(searchResults##data, engine)) {
  | Some(x) => x##url
  | None => ""
  };

[@bs.send.pipe: client]
external random : string => Js.Promise.t(singleResponse) = "";

let random = (tag, client) =>
  random(tag, client)
  |> Js.Promise.then_(response => Js.Promise.resolve(response##data##url));
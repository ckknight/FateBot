// Generated by BUCKLESCRIPT VERSION 3.1.1, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Utils = require("./Utils.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Js_undefined = require("bs-platform/lib/js/js_undefined.js");

var Collection = /* module */[];

function UserResolvable() {
  return /* module */[];
}

var Snowflake = /* module */[];

var Client = /* module */[];

function TextBasedChannel() {
  var send = function ($staropt$star, nonce, embed, disableEveryone, $staropt$star$1, code, split, reply, content, t) {
    var tts = $staropt$star ? $staropt$star[0] : false;
    var files = $staropt$star$1 ? $staropt$star$1[0] : /* array */[];
    return Utils.promiseMap(Utils.magicAsArray)(t.send(content, {
                    tts: tts,
                    nonce: Js_undefined.fromOption(nonce),
                    embed: Js_undefined.fromOption(embed),
                    disableEveryone: Js_undefined.fromOption(disableEveryone),
                    files: files,
                    code: Js_undefined.fromOption(code),
                    split: Js_undefined.fromOption(Belt_Option.map(split, (function (splitOptions) {
                                return {
                                        maxLength: Js_undefined.fromOption(splitOptions[/* maxLength */0]),
                                        char: splitOptions[/* char */1],
                                        prepend: splitOptions[/* prepend */2],
                                        append: splitOptions[/* append */3]
                                      };
                              }))),
                    reply: Js_undefined.fromOption(reply)
                  }));
  };
  return /* module */[/* send */send];
}

function reply($staropt$star, nonce, embed, disableEveryone, $staropt$star$1, code, split, content, t) {
  var tts = $staropt$star ? $staropt$star[0] : false;
  var files = $staropt$star$1 ? $staropt$star$1[0] : /* array */[];
  return Utils.promiseMap(Utils.magicAsArray)(t.reply(content, {
                  tts: tts,
                  nonce: Js_undefined.fromOption(nonce),
                  embed: Js_undefined.fromOption(embed),
                  disableEveryone: Js_undefined.fromOption(disableEveryone),
                  files: files,
                  code: Js_undefined.fromOption(code),
                  split: Js_undefined.fromOption(Belt_Option.map(split, (function (splitOptions) {
                              return {
                                      maxLength: Js_undefined.fromOption(splitOptions[/* maxLength */0]),
                                      char: splitOptions[/* char */1],
                                      prepend: splitOptions[/* prepend */2],
                                      append: splitOptions[/* append */3]
                                    };
                            }))),
                  reply: undefined
                }));
}

var Message = /* module */[/* reply */reply];

var Guild = /* module */[];

function Impl() {
  var classify = function (t) {
    var x = t.type;
    switch (x) {
      case "dm" : 
          return /* DM */Block.__(0, [t]);
      case "group" : 
          return /* Group */Block.__(1, [t]);
      case "text" : 
          return /* Text */Block.__(2, [t]);
      case "voice" : 
          return /* Voice */Block.__(3, [t]);
      default:
        return Pervasives.failwith("Unknown channelType " + x);
    }
  };
  return /* module */[/* classify */classify];
}

function classify(t) {
  var x = t.type;
  switch (x) {
    case "dm" : 
        return /* DM */Block.__(0, [t]);
    case "group" : 
        return /* Group */Block.__(1, [t]);
    case "text" : 
        return /* Text */Block.__(2, [t]);
    case "voice" : 
        return /* Voice */Block.__(3, [t]);
    default:
      return Pervasives.failwith("Unknown channelType " + x);
  }
}

var Channel = /* module */[
  /* Impl */Impl,
  /* classify */classify
];

function Impl$1() {
  var classify = function (t) {
    var x = t.type;
    switch (x) {
      case "dm" : 
          return /* DM */Block.__(0, [t]);
      case "group" : 
          return /* Group */Block.__(1, [t]);
      case "text" : 
          return /* Text */Block.__(2, [t]);
      case "voice" : 
          return /* Voice */Block.__(3, [t]);
      default:
        return Pervasives.failwith("Unknown channelType " + x);
    }
  };
  var send = function ($staropt$star, nonce, embed, disableEveryone, $staropt$star$1, code, split, reply, content, t) {
    var tts = $staropt$star ? $staropt$star[0] : false;
    var files = $staropt$star$1 ? $staropt$star$1[0] : /* array */[];
    return Utils.promiseMap(Utils.magicAsArray)(t.send(content, {
                    tts: tts,
                    nonce: Js_undefined.fromOption(nonce),
                    embed: Js_undefined.fromOption(embed),
                    disableEveryone: Js_undefined.fromOption(disableEveryone),
                    files: files,
                    code: Js_undefined.fromOption(code),
                    split: Js_undefined.fromOption(Belt_Option.map(split, (function (splitOptions) {
                                return {
                                        maxLength: Js_undefined.fromOption(splitOptions[/* maxLength */0]),
                                        char: splitOptions[/* char */1],
                                        prepend: splitOptions[/* prepend */2],
                                        append: splitOptions[/* append */3]
                                      };
                              }))),
                    reply: Js_undefined.fromOption(reply)
                  }));
  };
  return /* module */[
          /* classify */classify,
          /* send */send
        ];
}

function classify$1(t) {
  var x = t.type;
  switch (x) {
    case "dm" : 
        return /* DM */Block.__(0, [t]);
    case "group" : 
        return /* Group */Block.__(1, [t]);
    case "text" : 
        return /* Text */Block.__(2, [t]);
    case "voice" : 
        return /* Voice */Block.__(3, [t]);
    default:
      return Pervasives.failwith("Unknown channelType " + x);
  }
}

function send($staropt$star, nonce, embed, disableEveryone, $staropt$star$1, code, split, reply, content, t) {
  var tts = $staropt$star ? $staropt$star[0] : false;
  var files = $staropt$star$1 ? $staropt$star$1[0] : /* array */[];
  return Utils.promiseMap(Utils.magicAsArray)(t.send(content, {
                  tts: tts,
                  nonce: Js_undefined.fromOption(nonce),
                  embed: Js_undefined.fromOption(embed),
                  disableEveryone: Js_undefined.fromOption(disableEveryone),
                  files: files,
                  code: Js_undefined.fromOption(code),
                  split: Js_undefined.fromOption(Belt_Option.map(split, (function (splitOptions) {
                              return {
                                      maxLength: Js_undefined.fromOption(splitOptions[/* maxLength */0]),
                                      char: splitOptions[/* char */1],
                                      prepend: splitOptions[/* prepend */2],
                                      append: splitOptions[/* append */3]
                                    };
                            }))),
                  reply: Js_undefined.fromOption(reply)
                }));
}

var DMChannel = /* module */[
  /* Impl */Impl$1,
  /* classify */classify$1,
  /* send */send
];

function Impl$2() {
  var classify = function (t) {
    var x = t.type;
    switch (x) {
      case "dm" : 
          return /* DM */Block.__(0, [t]);
      case "group" : 
          return /* Group */Block.__(1, [t]);
      case "text" : 
          return /* Text */Block.__(2, [t]);
      case "voice" : 
          return /* Voice */Block.__(3, [t]);
      default:
        return Pervasives.failwith("Unknown channelType " + x);
    }
  };
  var $$delete = function (reason, t) {
    if (reason) {
      return t.delete(reason[0]);
    } else {
      return t.delete();
    }
  };
  var edit = function (reason, channelData, t) {
    if (reason) {
      return t.edit(channelData, reason[0]);
    } else {
      return t.edit(channelData);
    }
  };
  var setName = function (reason, name, t) {
    if (reason) {
      return t.setName(name, reason[0]);
    } else {
      return t.setName(name);
    }
  };
  var setTopic = function (reason, topic, t) {
    if (reason) {
      return t.setTopic(topic, reason[0]);
    } else {
      return t.setTopic(topic);
    }
  };
  return /* module */[
          /* classify */classify,
          /* delete */$$delete,
          /* edit */edit,
          /* setName */setName,
          /* setTopic */setTopic
        ];
}

function classify$2(t) {
  var x = t.type;
  switch (x) {
    case "dm" : 
        return /* DM */Block.__(0, [t]);
    case "group" : 
        return /* Group */Block.__(1, [t]);
    case "text" : 
        return /* Text */Block.__(2, [t]);
    case "voice" : 
        return /* Voice */Block.__(3, [t]);
    default:
      return Pervasives.failwith("Unknown channelType " + x);
  }
}

function $$delete(reason, t) {
  if (reason) {
    return t.delete(reason[0]);
  } else {
    return t.delete();
  }
}

function edit(reason, channelData, t) {
  if (reason) {
    return t.edit(channelData, reason[0]);
  } else {
    return t.edit(channelData);
  }
}

function setName(reason, name, t) {
  if (reason) {
    return t.setName(name, reason[0]);
  } else {
    return t.setName(name);
  }
}

function setTopic(reason, topic, t) {
  if (reason) {
    return t.setTopic(topic, reason[0]);
  } else {
    return t.setTopic(topic);
  }
}

var GuildChannel = /* module */[
  /* Impl */Impl$2,
  /* classify */classify$2,
  /* delete */$$delete,
  /* edit */edit,
  /* setName */setName,
  /* setTopic */setTopic
];

function Impl$3() {
  var classify = function (t) {
    var x = t.type;
    switch (x) {
      case "dm" : 
          return /* DM */Block.__(0, [t]);
      case "group" : 
          return /* Group */Block.__(1, [t]);
      case "text" : 
          return /* Text */Block.__(2, [t]);
      case "voice" : 
          return /* Voice */Block.__(3, [t]);
      default:
        return Pervasives.failwith("Unknown channelType " + x);
    }
  };
  var include = /* module */[/* classify */classify];
  var $$delete = function (reason, t) {
    if (reason) {
      return t.delete(reason[0]);
    } else {
      return t.delete();
    }
  };
  var edit = function (reason, channelData, t) {
    if (reason) {
      return t.edit(channelData, reason[0]);
    } else {
      return t.edit(channelData);
    }
  };
  var setName = function (reason, name, t) {
    if (reason) {
      return t.setName(name, reason[0]);
    } else {
      return t.setName(name);
    }
  };
  var setTopic = function (reason, topic, t) {
    if (reason) {
      return t.setTopic(topic, reason[0]);
    } else {
      return t.setTopic(topic);
    }
  };
  var send = function ($staropt$star, nonce, embed, disableEveryone, $staropt$star$1, code, split, reply, content, t) {
    var tts = $staropt$star ? $staropt$star[0] : false;
    var files = $staropt$star$1 ? $staropt$star$1[0] : /* array */[];
    return Utils.promiseMap(Utils.magicAsArray)(t.send(content, {
                    tts: tts,
                    nonce: Js_undefined.fromOption(nonce),
                    embed: Js_undefined.fromOption(embed),
                    disableEveryone: Js_undefined.fromOption(disableEveryone),
                    files: files,
                    code: Js_undefined.fromOption(code),
                    split: Js_undefined.fromOption(Belt_Option.map(split, (function (splitOptions) {
                                return {
                                        maxLength: Js_undefined.fromOption(splitOptions[/* maxLength */0]),
                                        char: splitOptions[/* char */1],
                                        prepend: splitOptions[/* prepend */2],
                                        append: splitOptions[/* append */3]
                                      };
                              }))),
                    reply: Js_undefined.fromOption(reply)
                  }));
  };
  return /* module */[
          /* classify */include[0],
          /* delete */$$delete,
          /* edit */edit,
          /* setName */setName,
          /* setTopic */setTopic,
          /* send */send
        ];
}

function classify$3(t) {
  var x = t.type;
  switch (x) {
    case "dm" : 
        return /* DM */Block.__(0, [t]);
    case "group" : 
        return /* Group */Block.__(1, [t]);
    case "text" : 
        return /* Text */Block.__(2, [t]);
    case "voice" : 
        return /* Voice */Block.__(3, [t]);
    default:
      return Pervasives.failwith("Unknown channelType " + x);
  }
}

var include = /* module */[/* classify */classify$3];

function $$delete$1(reason, t) {
  if (reason) {
    return t.delete(reason[0]);
  } else {
    return t.delete();
  }
}

function edit$1(reason, channelData, t) {
  if (reason) {
    return t.edit(channelData, reason[0]);
  } else {
    return t.edit(channelData);
  }
}

function setName$1(reason, name, t) {
  if (reason) {
    return t.setName(name, reason[0]);
  } else {
    return t.setName(name);
  }
}

function setTopic$1(reason, topic, t) {
  if (reason) {
    return t.setTopic(topic, reason[0]);
  } else {
    return t.setTopic(topic);
  }
}

function send$1($staropt$star, nonce, embed, disableEveryone, $staropt$star$1, code, split, reply, content, t) {
  var tts = $staropt$star ? $staropt$star[0] : false;
  var files = $staropt$star$1 ? $staropt$star$1[0] : /* array */[];
  return Utils.promiseMap(Utils.magicAsArray)(t.send(content, {
                  tts: tts,
                  nonce: Js_undefined.fromOption(nonce),
                  embed: Js_undefined.fromOption(embed),
                  disableEveryone: Js_undefined.fromOption(disableEveryone),
                  files: files,
                  code: Js_undefined.fromOption(code),
                  split: Js_undefined.fromOption(Belt_Option.map(split, (function (splitOptions) {
                              return {
                                      maxLength: Js_undefined.fromOption(splitOptions[/* maxLength */0]),
                                      char: splitOptions[/* char */1],
                                      prepend: splitOptions[/* prepend */2],
                                      append: splitOptions[/* append */3]
                                    };
                            }))),
                  reply: Js_undefined.fromOption(reply)
                }));
}

var TextChannel_001 = /* classify */include[0];

var TextChannel = /* module */[
  /* Impl */Impl$3,
  TextChannel_001,
  /* delete */$$delete$1,
  /* edit */edit$1,
  /* setName */setName$1,
  /* setTopic */setTopic$1,
  /* send */send$1
];

function encodePresenceStatus(x) {
  switch (x) {
    case 0 : 
        return "online";
    case 1 : 
        return "idle";
    case 2 : 
        return "invisible";
    case 3 : 
        return "dnd";
    
  }
}

var Presence = /* module */[/* encodePresenceStatus */encodePresenceStatus];

function Impl$4() {
  return /* module */[];
}

var User = /* module */[/* Impl */Impl$4];

function Impl$5() {
  var setPresence = function ($staropt$star, $staropt$star$1, $staropt$star$2, $staropt$star$3, user) {
    var status = $staropt$star ? $staropt$star[0] : /* Online */0;
    var afk = $staropt$star$1 ? $staropt$star$1[0] : false;
    var game = $staropt$star$2 ? $staropt$star$2[0] : "";
    var gameUrl = $staropt$star$3 ? $staropt$star$3[0] : "";
    return user.setPresence({
                status: encodePresenceStatus(status),
                afk: afk,
                game: {
                  name: game,
                  url: gameUrl
                }
              });
  };
  return /* module */[/* setPresence */setPresence];
}

function setPresence($staropt$star, $staropt$star$1, $staropt$star$2, $staropt$star$3, user) {
  var status = $staropt$star ? $staropt$star[0] : /* Online */0;
  var afk = $staropt$star$1 ? $staropt$star$1[0] : false;
  var game = $staropt$star$2 ? $staropt$star$2[0] : "";
  var gameUrl = $staropt$star$3 ? $staropt$star$3[0] : "";
  return user.setPresence({
              status: encodePresenceStatus(status),
              afk: afk,
              game: {
                name: game,
                url: gameUrl
              }
            });
}

var ClientUser = /* module */[
  /* Impl */Impl$5,
  /* setPresence */setPresence
];

function send$2($staropt$star, nonce, embed, disableEveryone, $staropt$star$1, code, split, reply, content, t) {
  var tts = $staropt$star ? $staropt$star[0] : false;
  var files = $staropt$star$1 ? $staropt$star$1[0] : /* array */[];
  return Utils.promiseMap(Utils.magicAsArray)(t.send(content, {
                  tts: tts,
                  nonce: Js_undefined.fromOption(nonce),
                  embed: Js_undefined.fromOption(embed),
                  disableEveryone: Js_undefined.fromOption(disableEveryone),
                  files: files,
                  code: Js_undefined.fromOption(code),
                  split: Js_undefined.fromOption(Belt_Option.map(split, (function (splitOptions) {
                              return {
                                      maxLength: Js_undefined.fromOption(splitOptions[/* maxLength */0]),
                                      char: splitOptions[/* char */1],
                                      prepend: splitOptions[/* prepend */2],
                                      append: splitOptions[/* append */3]
                                    };
                            }))),
                  reply: Js_undefined.fromOption(reply)
                }));
}

var GuildMember = /* module */[/* send */send$2];

var Author = /* module */[];

var Field = /* module */[];

var Footer = /* module */[];

var Image = /* module */[];

var Provider = /* module */[];

var Thumbnail = /* module */[];

var Video = /* module */[];

var MessageEmbed = /* module */[
  /* Author */Author,
  /* Field */Field,
  /* Footer */Footer,
  /* Image */Image,
  /* Provider */Provider,
  /* Thumbnail */Thumbnail,
  /* Video */Video
];

var RichEmbed = /* module */[];

function rgb(r, g, b) {
  return /* array */[
          r,
          g,
          b
        ];
}

var ColorResolvable = /* module */[/* rgb */rgb];

function make(name, attachment) {
  return {
          attachment: attachment,
          name: Js_undefined.fromOption(name)
        };
}

var FileOptions = /* module */[/* make */make];

var BufferResolvable = /* module */[];

function make$1(maxLength, $$char, prepend, append, _) {
  return /* record */[
          /* maxLength */maxLength,
          /* char */Belt_Option.getWithDefault($$char, "\n"),
          /* prepend */Belt_Option.getWithDefault(prepend, ""),
          /* append */Belt_Option.getWithDefault(append, "")
        ];
}

var SplitOptions = /* module */[/* make */make$1];

exports.Collection = Collection;
exports.UserResolvable = UserResolvable;
exports.Snowflake = Snowflake;
exports.Client = Client;
exports.TextBasedChannel = TextBasedChannel;
exports.Message = Message;
exports.Guild = Guild;
exports.Channel = Channel;
exports.DMChannel = DMChannel;
exports.GuildChannel = GuildChannel;
exports.TextChannel = TextChannel;
exports.Presence = Presence;
exports.User = User;
exports.ClientUser = ClientUser;
exports.GuildMember = GuildMember;
exports.MessageEmbed = MessageEmbed;
exports.RichEmbed = RichEmbed;
exports.ColorResolvable = ColorResolvable;
exports.FileOptions = FileOptions;
exports.BufferResolvable = BufferResolvable;
exports.SplitOptions = SplitOptions;
/* No side effect */

type snowflake;

type collection('k, 'v);

type channelLogsQueryOptions;

type client;

type clientUser;

type clientUserGuildSettings;

type clientUserSettings;

type channel;

type fileOptions;

type groupDMChannel;

type channelData;

type emoji;

type permissions;

type guild;

type guildChannel;

type guildMember;

type invite;

type presence;

type presenceStatus =
  | Online
  | Idle
  | Invisible
  | DND;

type user;

type voiceBroadcast;

type voiceChannel;

type voiceConnection;

type voiceRegion;

type webhook;

type message;

type messageAttachment;

type messageEmbed;

type messageEmbedAuthor;

type messageEmbedField;

type messageEmbedFooter;

type messageEmbedImage;

type messageEmbedProvider;

type messageEmbedThumbnail;

type messageEmbedVideo;

type messageMentions;

type messageReaction;

type role;

type reactionEmoji;

type textChannel;

type dmChannel;

type permissionOverwrites;

type userResolvable;

type richEmbed;

type colorResolvable;

type bufferResolvable;

type splitOptions = {
  maxLength: option(int),
  char: string,
  prepend: string,
  append: string
};

module Collection = {
  type t('k, 'v) = collection('k, 'v);
  [@bs.get] external size : t('k, 'v) => int = "";
  [@bs.send] external clear : t('k, 'v) => unit = "";
  [@bs.send.pipe : t('k, 'v)] external delete : 'k => bool = "";
  [@bs.send.pipe : t('k, 'v)] external forEach : ('v => unit) => unit = "";
  [@bs.send.pipe : t('k, 'v)]
  external forEachi : ([@bs] (('v, 'k) => unit)) => unit =
    "forEach";
  [@bs.send.pipe : t('k, 'v)] [@bs.return undefined_to_opt]
  external get : 'k => option('v) =
    "";
  [@bs.send.pipe : t('k, 'v)] external has : 'k => bool = "";
  [@bs.send.pipe : t('k, 'v)] external set : ('k, 'v) => unit = "";
  [@bs.send] external array : t('k, 'v) => array('v) = "";
  [@bs.send] external clone : t('k, 'v) => t('k, 'v) = "";
  [@bs.send] external concat : (t('k, 'v), t('k, 'v)) => t('k, 'v) = "";
  [@bs.send] external deleteAll : t('k, 'v) => Js.Promise.t(array('a)) = "";
  [@bs.send] external equals : (t('k, 'v), t('k, 'v)) => bool = "";
  [@bs.send.pipe : t('k, 'v)] external every : ('v => bool) => bool = "";
  [@bs.send.pipe : t('k, 'v)]
  external everyi : ([@bs] (('v, 'k) => bool)) => bool =
    "every";
  [@bs.send.pipe : t('k, 'v)] external exists : (string, 'a) => bool = "";
  [@bs.send.pipe : t('k, 'v)] external filter : ('v => bool) => t('k, 'v) = "";
  [@bs.send.pipe : t('k, 'v)]
  external filteri : ([@bs] (('v, 'k) => bool)) => t('k, 'v) =
    "filter";
  [@bs.send.pipe : t('k, 'v)]
  external filterArray : ('v => bool) => array('v) =
    "";
  [@bs.send.pipe : t('k, 'v)]
  external filterArrayi : ([@bs] (('v, 'k) => bool)) => array('v) =
    "filterArray";
  [@bs.send.pipe : t('k, 'v)] [@bs.return nullable]
  external find : ('v => bool) => option('v) =
    "";
  [@bs.send.pipe : t('k, 'v)] [@bs.return nullable]
  external findi : ([@bs] (('v, 'k) => bool)) => option('v) =
    "find";
  [@bs.send.pipe : t('k, 'v)] [@bs.return nullable]
  external findByProp : (string, 'a) => option('v) =
    "find";
  [@bs.send.pipe : t('k, 'v)] external findAll : (string, 'a) => array('v) =
    "";
  [@bs.send.pipe : t('k, 'v)] [@bs.return nullable]
  external findKey : ('v => bool) => option('k) =
    "";
  [@bs.send.pipe : t('k, 'v)] [@bs.return nullable]
  external findKeyi : ([@bs] (('v, 'k) => bool)) => option('k) =
    "findKey";
  [@bs.send.pipe : t('k, 'v)]
  external findKeyByProp : (string, 'a) => Js.null('k) =
    "findKey";
  [@bs.send] [@bs.return nullable] external first : t('k, 'v) => option('v) =
    "";
  [@bs.send.pipe : t('k, 'v)] external firstValues : int => array('v) =
    "first";
  [@bs.send] [@bs.return nullable]
  external firstKey : t('k, 'v) => option('k) =
    "";
  [@bs.send.pipe : t('k, 'v)] external firstKeys : int => array('k) =
    "firstKey";
  [@bs.send] external keyArray : t('k, 'v) => array('k) = "";
  [@bs.send] [@bs.return nullable] external last : t('k, 'v) => option('v) =
    "";
  [@bs.send.pipe : t('k, 'v)] external lastValues : int => array('v) = "last";
  [@bs.send] [@bs.return nullable] external lastKey : t('k, 'v) => option('k) =
    "";
  [@bs.send.pipe : t('k, 'v)] external lastKeys : int => array('k) = "lastKey";
  [@bs.send.pipe : t('k, 'v)] external map : ('v => 'x) => array('x) = "";
  [@bs.send.pipe : t('k, 'v)]
  external mapi : ([@bs] (('v, 'k) => 'x)) => array('x) =
    "map";
  [@bs.send] [@bs.return nullable] external random : t('k, 'v) => option('v) =
    "";
  [@bs.send.pipe : t('k, 'v)] external randomValues : int => array('v) =
    "random";
  [@bs.send] [@bs.return nullable]
  external randomKey : t('k, 'v) => option('k) =
    "";
  [@bs.send.pipe : t('k, 'v)] external randomKeys : int => array('k) =
    "randomKey";
  [@bs.send.pipe : t('k, 'v)]
  external reduce : ([@bs] (('a, 'v) => 'a), 'a) => 'a =
    "";
  [@bs.send.pipe : t('k, 'v)]
  external reducei : ([@bs] (('a, 'v, 'k) => 'a), 'a) => 'a =
    "reduce";
  [@bs.send.pipe : t('k, 'v)] external some : ('v => bool) => bool = "";
  [@bs.send.pipe : t('k, 'v)]
  external somei : ([@bs] (('v, 'k) => bool)) => bool =
    "some";
  [@bs.send] external sort : t('k, 'v) => t('k, 'v) = "";
  [@bs.send.pipe : t('k, 'v)]
  external sortWith : ([@bs] (('v, 'v) => int)) => t('k, 'v) =
    "sort";
  external sortWithi : ([@bs] (('v, 'v, 'k, 'k) => int)) => t('k, 'v) = "sort";
};

module UserResolvable (U: {type t;}) = {
  external userResolvable : U.t => userResolvable = "%identity";
};

module Snowflake = {
  type t = snowflake;
  external ofString : string => t = "%identity";
  external toString : t => string = "%identity";
  include
    UserResolvable(
      {
        type nonrec t = t;
      }
    );
};

module Client = {
  type t = client;
  type interval;
  type timeout;
  [@bs.module "discord.js"] [@bs.new] external make : unit => t = "Client";
  [@bs.get] external broadcasts : t => array(voiceBroadcast) = "";
  [@bs.get] external browser : t => bool = "";
  [@bs.get] external channels : t => collection(snowflake, channel) = "";
  [@bs.get] external emojis : t => collection(snowflake, emoji) = "";
  [@bs.get] external guilds : t => collection(snowflake, guild) = "";
  [@bs.get] external ping : t => float = "";
  [@bs.get] external pings : t => array(float) = "";
  /* This is only filled when using a user account. */
  [@bs.get] external presences : t => collection(snowflake, presence) = "";
  [@bs.get] [@bs.return nullable] external readyAt : t => option(Js.Date.t) =
    "";
  [@bs.get] [@bs.return nullable]
  external readyTimestamp : t => option(float) =
    "";
  /*
   .shard
   The shard helpers for the client (only if the process was spawned as a child, such as from a ShardingManager)

   Type: ?ShardClientUtil
   */
  /* TODO: see if this is float or int */
  [@bs.get] [@bs.return nullable] external status : t => option(float) = "";
  [@bs.get] [@bs.return nullable] external token : t => option(string) = "";
  [@bs.get] [@bs.return nullable] external uptime : t => option(float) = "";
  [@bs.get] [@bs.return nullable] external user : t => option(clientUser) = "";
  [@bs.get] external users : t => collection(snowflake, user) = "";
  [@bs.get]
  external voiceConnections : t => collection(snowflake, voiceConnection) =
    "";
  [@bs.send] external clearTimeout : (t, timeout) => unit = "";
  [@bs.send] external clearInterval : (t, interval) => unit = "";
  [@bs.send] external setTimeout : (t, unit => unit, int) => timeout = "";
  [@bs.send] external setInterval : (t, unit => unit, int) => interval = "";
  [@bs.send] external createVoiceBroadcast : t => voiceBroadcast = "";
  [@bs.send] external destroy : t => Js.Promise.t('a) = "";
  type oauth2Application;
  [@bs.send.pipe : t]
  external fetchApplication : snowflake => Js.Promise.t(oauth2Application) =
    "";
  [@bs.send]
  external fetchMyApplication : t => Js.Promise.t(oauth2Application) =
    "";
  [@bs.send.pipe : t] external fetchInvite : string => Js.Promise.t(invite) =
    "";
  [@bs.send.pipe : t] external fetchUser : snowflake => Js.Promise.t(user) =
    "";
  /* This is only available when using a bot account. */
  [@bs.send.pipe : t]
  external fetchUserUncached :
    (snowflake, [@bs.as {json|false|json}] _) => Js.Promise.t(user) =
    "fetchUser";
  [@bs.send]
  external fetchVoiceRegions :
    t => Js.Promise.t(collection(string, voiceRegion)) =
    "";
  [@bs.send.pipe : t]
  external fetchWebhook : snowflake => Js.Promise.t(webhook) =
    "";
  [@bs.send.pipe : t]
  external fetchWebhookWithToken : (snowflake, string) => Js.Promise.t(webhook) =
    "fetchWebhook";
  [@bs.send.pipe : t] external generateInvite : int => Js.Promise.t(string) =
    "";
  [@bs.send.pipe : t] external login : string => unit = "";
  [@bs.send] external sweepMessages : t => int = "";
  [@bs.send.pipe : t] external sweepMessagesOlderThan : int => int = "";
  /* .syncGuilds(guilds)
     Requests a sync of guild data with Discord.

     This can be done automatically every 30 seconds by enabling ClientOptions#sync. This is only available when using a user account.

     PARAMETER	TYPE	OPTIONAL	DEFAULT	DESCRIPTION
     guilds	Array<Guild> Collection<Snowflake, Guild>		this.guilds
     An array or collection of guilds to sync

     Returns: void */
  [@bs.send.pipe : t]
  external onChannelCreate :
    ([@bs.as "channelCreate"] _, channel => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onChannelDelete :
    ([@bs.as "channelDelete"] _, channel => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onChannelPinsUpdate :
    ([@bs.as "channelPinsUpdate"] _, (channel, Js.Date.t) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onChannelUpdate :
    ([@bs.as "channelUpdate"] _, (channel, channel) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onClientUserGuildSettingsUpdate :
    (
      [@bs.as "clientUserGuildSettingsUpdate"] _,
      clientUserGuildSettings => unit
    ) =>
    unit =
    "on";
  [@bs.send.pipe : t]
  external onClientUserSettingsUpdate :
    ([@bs.as "clientUserSettingsUpdate"] _, clientUserSettings => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onDebug : ([@bs.as "debug"] _, string => unit) => unit =
    "on";
  /* NOTE: onDisconnect callback actually takes CloseEvent, not unit */
  [@bs.send.pipe : t]
  external onDisconnect : ([@bs.as "disconnect"] _, unit => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onEmojiCreate : ([@bs.as "emojiCreate"] _, emoji => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onEmojiDelete : ([@bs.as "emojiDelete"] _, emoji => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onEmojiUpdate :
    ([@bs.as "emojiUpdate"] _, (emoji, emoji) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onError : ([@bs.as "error"] _, Js.Exn.t => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildBanAdd :
    ([@bs.as "guildBanAdd"] _, (guild, user) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildBanRemove :
    ([@bs.as "guildBanRemove"] _, (guild, user) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildCreate : ([@bs.as "guildCreate"] _, guild => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildDelete : ([@bs.as "guildDelete"] _, guild => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildMemberAdd :
    ([@bs.as "guildMemberAdd"] _, guildMember => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildMemberAvailable :
    ([@bs.as "guildMemberAvailable"] _, guildMember => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildMemberRemove :
    ([@bs.as "guildMemberRemove"] _, guildMember => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildMembersChunk :
    ([@bs.as "guildMembersChunk"] _, (array(guildMember), guild) => unit) =>
    unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildMemberSpeaking :
    ([@bs.as "guildMemberSpeaking"] _, (guildMember, bool) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildMemberUpdate :
    ([@bs.as "guildMemberUpdate"] _, (guildMember, guildMember) => unit) =>
    unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildUnavailable :
    ([@bs.as "guildUnavailable"] _, guild => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onGuildUpdate :
    ([@bs.as "onGuildUpdate"] _, (guild, guild) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onMessage : ([@bs.as "message"] _, message => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onMessageDelete :
    ([@bs.as "messageDelete"] _, message => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onMessageDeleteBulk :
    ([@bs.as "messageDeleteBulk"] _, collection(snowflake, message) => unit) =>
    unit =
    "on";
  [@bs.send.pipe : t]
  external onMessageReactionAdd :
    ([@bs.as "messageReactionAdd"] _, (messageReaction, user) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onMessageReactionRemove :
    ([@bs.as "messageReactionRemove"] _, (messageReaction, user) => unit) =>
    unit =
    "on";
  [@bs.send.pipe : t]
  external onMessageReactionRemoveAll :
    ([@bs.as "messageReactionRemoveAll"] _, messageReaction => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onMessageUpdate :
    ([@bs.as "messageUpdate"] _, (message, message) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onPresenceUpdate :
    ([@bs.as "presenceUpdate"] _, (guildMember, guildMember) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onReady : ([@bs.as "ready"] _, unit => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onReconnecting : ([@bs.as "reconnecting"] _, unit => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onResume : ([@bs.as "resume"] _, int => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onRoleCreate : ([@bs.as "roleCreate"] _, role => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onRoleDelete : ([@bs.as "roleDelete"] _, role => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onRoleUpdate :
    ([@bs.as "roleUpdate"] _, (role, role) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onTypingStart :
    ([@bs.as "typingStart"] _, (channel, user) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onTypingStop :
    ([@bs.as "typingStop"] _, (channel, user) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onUserNoteUpdate :
    ([@bs.as "userNoteUpdate"] _, (user, string, string) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onUserUpdate :
    ([@bs.as "userUpdate"] _, (user, user) => unit) => unit =
    "on";
  [@bs.send.pipe : t]
  external onVoiceStatusUpdate :
    ([@bs.as "voiceStatusUpdate"] _, (guildMember, guildMember) => unit) =>
    unit =
    "on";
  [@bs.send.pipe : t]
  external onWarn : ([@bs.as "warn"] _, string => unit) => unit =
    "on";
};

type messageOptions =
  Js.t(
    {
      .
      tts: Js.boolean,
      nonce: Js.undefined(string),
      embed: Js.undefined(richEmbed),
      disableEveryone:
        Js.undefined(
          Js.boolean
        ), /* defaults to this.client.options.disableEveryone */
      files: array(fileOptions),
      code: Js.undefined(string),
      split:
        Js.undefined(
          Js.t(
            {
              .
              maxLength: Js.undefined(int), /* default: 1950 */
              char: string, /* default: "\n" */
              prepend: string, /* default: "" */
              append:
                string /* default: "" */
            }
          )
        ),
      reply: Js.undefined(userResolvable)
    }
  );

module TextBasedChannel (C: {type t;}) = {
  [@bs.get] [@bs.return nullable]
  external lastMessageID : C.t => option(snowflake) =
    "";
  [@bs.get] [@bs.return nullable]
  external lastMessage : C.t => option(message) =
    "";
  /* note: this return type is a lie, it could be message | array(message) */
  [@bs.send.pipe : C.t]
  external send : (string, messageOptions) => Js.Promise.t(message) =
    "";
  let send
      (
        :tts=false,
        :nonce=?,
        :embed=?,
        :disableEveryone=?,
        :files=[||],
        :code=?,
        :split=?,
        :reply=?,
        content,
        t
      ) =
    send(
      content,
      {
        "tts": tts |> Js.Boolean.to_js_boolean,
        "nonce": nonce |> Js.Undefined.from_opt,
        "embed": embed |> Js.Undefined.from_opt,
        "disableEveryone":
          disableEveryone
          |> Utils.Option.map(Js.Boolean.to_js_boolean)
          |> Js.Undefined.from_opt,
        "files": files,
        "code": code |> Js.Undefined.from_opt,
        "split":
          split
          |> Utils.Option.map(
               (splitOptions) => {
                 "maxLength": splitOptions.maxLength |> Js.Undefined.from_opt,
                 "char": splitOptions.char,
                 "prepend": splitOptions.prepend,
                 "append": splitOptions.append
               }
             )
          |> Js.Undefined.from_opt,
        "reply": reply |> Js.Undefined.from_opt
      },
      t
    )
    |> Utils.promiseMap(Utils.magicAsArray);
};

module Message = {
  type t = message;
  [@bs.get]
  external attachments : t => collection(snowflake, messageAttachment) =
    "";
  [@bs.get] external author : t => user = "";
  /* channel: TextChannel | DMChannel | GroupDMChannel, */
  [@bs.get] external channel : t => channel = "";
  [@bs.get] external cleanContent : t => string = "";
  [@bs.get] external client : t => client = "";
  [@bs.get] external content : t => string = "";
  [@bs.get] external createdAt : t => Js.Date.t = "";
  [@bs.get] external createdTimestamp : t => float = "";
  [@bs.get] external deletable : t => bool = "";
  [@bs.get] external editable : t => bool = "";
  [@bs.get] external editedAt : t => Js.Date.t = "";
  [@bs.get] external editedTimestamp : t => float = "";
  [@bs.get] external edits : t => array(t) = "";
  [@bs.get] external embeds : t => array(messageEmbed) = "";
  [@bs.get] [@bs.return nullable] external guild : t => option(guild) = "";
  [@bs.get] external hit : t => bool = "";
  [@bs.get] external id : t => snowflake = "";
  [@bs.get] external member : t => guildMember = "";
  [@bs.get] external mentions : t => messageMentions = "";
  [@bs.get] external nonce : t => string = "";
  [@bs.get] external pinnable : t => bool = "";
  [@bs.get] external pinned : t => bool = "";
  [@bs.get] external reactions : t => collection(snowflake, messageReaction) =
    "";
  [@bs.get] external system : t => bool = "";
  [@bs.get] external tts : t => bool = "";
  [@bs.get] external messageType : t => string = "";
  [@bs.get] external webhookID : t => snowflake = "";
  /* This is only available when using a user account. */
  [@bs.send] external acknowledge : t => Js.Promise.t(t) = "";
  /* awaitReactions(
       filter: CollectorFilter,
       options?: AwaitReactionsOptions,
     ): Promise<Collection<Snowflake, MessageReaction>>, */
  [@bs.send] external clearReactions : t => Js.Promise.t(t) = "";
  /* createReactionCollector(
       filter: CollectorFilter,
       options?: ReactionCollectorOptions,
     ): ReactionCollector, */
  /* delete(timeout?: number): Promise<Message>, */
  [@bs.send] external delete : t => Js.Promise.t(t) = "";
  [@bs.send.pipe : t] external deleteWithTimeout : float => Js.Promise.t(t) =
    "delete";
  /* edit(
       content: StringResolvable,
       options?: MessageEditOptions,
     ): Promise<Message>, */
  [@bs.send] external equals : (t, t, 'a) => bool = "";
  [@bs.send] external fetchWebhook : t => Js.Promise.t(Js.nullable(webhook)) =
    "";
  /* isMemberMentioned(member: GuildMember | User): boolean, */
  [@bs.send.pipe : t] external isMemberMentioned : user => Js.Promise.t(t) =
    "";
  [@bs.send.pipe : t]
  external isGuildMemberMentioned : guildMember => Js.Promise.t(t) =
    "isMemberMentioned";
  /* isMentioned(data: GuildChannel | User | Role | Snowflake): boolean, */
  [@bs.send.pipe : t]
  external isGuildChannelMentioned : guildChannel => Js.Promise.t(t) =
    "isMentioned";
  [@bs.send.pipe : t] external isUserMentioned : user => Js.Promise.t(t) =
    "isMentioned";
  [@bs.send.pipe : t] external isRoleMentioned : role => Js.Promise.t(t) =
    "isMentioned";
  [@bs.send.pipe : t] external isMentioned : snowflake => Js.Promise.t(bool) =
    "";
  [@bs.send] external pin : t => Js.Promise.t(t) = "";
  [@bs.send.pipe : t] external react : emoji => Js.Promise.t(messageReaction) =
    "";
  [@bs.send.pipe : t]
  external reactWithString : string => Js.Promise.t(messageReaction) =
    "react";
  [@bs.send.pipe : t]
  external reactWithReactionEmoji :
    reactionEmoji => Js.Promise.t(messageReaction) =
    "react";
  [@bs.send] external unpin : t => Js.Promise.t(t) = "";
  /* note: this return type is a lie, it could be message | array(message) */
  [@bs.send.pipe : t]
  external reply : (string, messageOptions) => Js.Promise.t(message) =
    "";
  let reply
      (
        :tts=false,
        :nonce=?,
        :embed=?,
        :disableEveryone=?,
        :files=[||],
        :code=?,
        :split=?,
        content,
        t
      ) =
    reply(
      content,
      {
        "tts": tts |> Js.Boolean.to_js_boolean,
        "nonce": nonce |> Js.Undefined.from_opt,
        "embed": embed |> Js.Undefined.from_opt,
        "disableEveryone":
          disableEveryone
          |> Utils.Option.map(Js.Boolean.to_js_boolean)
          |> Js.Undefined.from_opt,
        "files": files,
        "code": code |> Js.Undefined.from_opt,
        "split":
          split
          |> Utils.Option.map(
               (splitOptions) => {
                 "maxLength": splitOptions.maxLength |> Js.Undefined.from_opt,
                 "char": splitOptions.char,
                 "prepend": splitOptions.prepend,
                 "append": splitOptions.append
               }
             )
          |> Js.Undefined.from_opt,
        "reply": Js.Undefined.empty
      },
      t
    )
    |> Utils.promiseMap(Utils.magicAsArray);
  include
    UserResolvable(
      {
        type nonrec t = t;
      }
    );
};

module Guild = {
  type t = guild;
  [@bs.get] [@bs.return nullable]
  external afkChannel : t => option(voiceChannel) =
    "";
  [@bs.get] [@bs.return nullable] external afkChannelId : t => option(string) =
    "";
  [@bs.get] [@bs.return nullable] external afkTimeout : t => option(float) =
    "";
  [@bs.get] [@bs.return nullable]
  external applicationID : t => option(snowflake) =
    "";
  [@bs.get] external available : t => bool = "";
  [@bs.get] external channels : t => collection(snowflake, guildChannel) = "";
  [@bs.get] external client : t => client = "";
  [@bs.get] external createdAt : t => Js.Date.t = "";
  [@bs.get] external createdTimestamp : t => float = "";
  [@bs.get] external defaultChannel : t => textChannel = "";
  [@bs.get] external defaultRole : t => role = "";
  [@bs.get] external embedEnabled : t => bool = "";
  [@bs.get] external emojis : t => collection(snowflake, emoji) = "";
  [@bs.get] external explicitContentFilter : t => int = "";
  /* features: Array<Object> */
  [@bs.get] [@bs.return nullable] external icon : t => option(string) = "";
  [@bs.get] [@bs.return nullable] external iconURL : t => option(string) = "";
  [@bs.get] external id : t => snowflake = "";
  [@bs.get] external joinedAt : t => Js.Date.t = "";
  [@bs.get] external joinedTimestamp : t => float = "";
  [@bs.get] external large : t => bool = "";
  [@bs.get] [@bs.return nullable] external me : t => option(guildMember) = "";
  [@bs.get] external memberCount : t => int = "";
  [@bs.get] external members : t => collection(snowflake, guildMember) = "";
  [@bs.get] external name : t => string = "";
  [@bs.get] external nameAcronym : t => string = "";
  [@bs.get] external owner : t => guildMember = "";
  [@bs.get] external ownerID : t => snowflake = "";
  [@bs.get] external presences : t => collection(snowflake, presence) = "";
  [@bs.get] external region : t => string = "";
  [@bs.get] external roles : t => collection(snowflake, role) = "";
  [@bs.get] [@bs.return nullable] external splash : t => option(string) = "";
  [@bs.get] [@bs.return nullable] external splashURL : t => option(string) =
    "";
  [@bs.get] [@bs.return nullable]
  external systemChannel : t => option(guildChannel) =
    "";
  [@bs.get] [@bs.return nullable]
  external systemChannelID : t => option(snowflake) =
    "";
  [@bs.get] external verificationLevel : t => int = "";
  [@bs.get] [@bs.return nullable]
  external voiceConnection : t => option(voiceConnection) =
    "";
  include
    UserResolvable(
      {
        type nonrec t = t;
      }
    );
};

module Channel = {
  type classifiedChannel =
    | DM(dmChannel)
    | Group(groupDMChannel)
    | Text(textChannel)
    | Voice(voiceChannel);
  module Impl (C: {type t;}) = {
    [@bs.get] external client : C.t => client = "";
    [@bs.get] external createdAt : C.t => Js.Date.t = "";
    [@bs.get] external createdTimestamp : C.t => float = "";
    [@bs.get] external id : C.t => snowflake = "";
    /* type: 'dm' | 'group' | 'text' | 'voice', */
    [@bs.get] external channelType : C.t => string = "type";
    [@bs.send] external delete : C.t => Js.Promise.t(C.t) = "";
    let classify (t) =
      switch (t |> channelType) {
      | "dm" => DM(Obj.magic(t))
      | "group" => Group(Obj.magic(t))
      | "text" => Text(Obj.magic(t))
      | "voice" => Voice(Obj.magic(t))
      | x => failwith("Unknown channelType " ++ x)
      };
  };
  type t = channel;
  include
    Impl(
      {
        type nonrec t = t;
      }
    );
};

module DMChannel = {
  module Impl (C: {type t;}) = {
    include
      Channel.Impl(
        {
          type nonrec t = C.t;
        }
      );
    include
      TextBasedChannel(
        {
          type nonrec t = C.t;
        }
      );
    [@bs.get] external recipient : C.t => user = "";
    [@bs.get] external typing : C.t => bool = "";
    [@bs.get] external typingCount : C.t => int = "";
  };
  type t = dmChannel;
  include
    Impl(
      {
        type nonrec t = t;
      }
    );
};

module GuildChannel = {
  module Impl (C: {type t;}) = {
    include
      Channel.Impl(
        {
          type nonrec t = C.t;
        }
      );
    [@bs.get] external calculatedPosition : C.t => int = "";
    [@bs.get] external deletable : C.t => bool = "";
    [@bs.get] external guild : C.t => guild = "";
    /*
     .messageNotifications READ-ONLY
     The type of message that should notify you

     This is only available when using a user account.

     Type: ?MessageNotificationType
     */
    /* This is only available when using a user account. */
    [@bs.get] [@bs.return nullable] external muted : C.t => option(bool) = "";
    [@bs.get] external name : C.t => string = "";
    [@bs.get]
    external permissionOverwrites :
      C.t => collection(snowflake, permissionOverwrites) =
      "";
    [@bs.get] external position : C.t => int = "";
    /* [@bs.send.pipe : C.t] external clone : (

       ) => Js.Promise.t(guildChannel) */
    /* [@bs.send.pipe : C.t] external createInvite : (

       ) => Js.Promise.t(invite) */
    [@bs.send.pipe : C.t]
    external deleteWithReason : string => Js.Promise.t(C.t) =
      "delete";
    let delete (:reason=?, t) =
      switch (reason) {
      | None => delete(t)
      | Some(x) => deleteWithReason(x, t)
      };
    [@bs.send.pipe : C.t] external edit : channelData => Js.Promise.t(C.t) =
      "";
    [@bs.send.pipe : C.t]
    external editWithReason : (channelData, string) => Js.Promise.t(C.t) =
      "edit";
    let edit (:reason=?, channelData, t) =
      switch (reason) {
      | None => edit(channelData, t)
      | Some(x) => editWithReason(channelData, x, t)
      };
    [@bs.send] external equals : (C.t, C.t) => bool = "";
    /*
     .overwritePermissions(userOrRoleoptionsreason)
     Overwrites the permissions for a user or role in this channel.

     PARAMETER	TYPE	OPTIONAL	DEFAULT	DESCRIPTION
     userOrRole	Role Snowflake UserResolvable
     The user or role to update

     options	PermissionOverwriteOptions
     The configuration for the update

     reason	string		none
     Reason for creating/editing this overwrite

     Returns: Promise
     Examples:
     // Overwrite permissions for a message author
     message.channel.overwritePermissions(message.author, {
       SEND_MESSAGES: false
     })
       .then(() => console.log('Done!'))
       .catch(console.error);
     */
    [@bs.send.pipe : C.t] [@bs.return nullable]
    external permissionsFor : user => option(permissions) =
      "";
    [@bs.send.pipe : C.t] [@bs.return nullable]
    external permissionsForMember : guildMember => option(permissions) =
      "permissionsFor";
    [@bs.send.pipe : C.t] external setName : string => Js.Promise.t(C.t) = "";
    [@bs.send.pipe : C.t]
    external setNameWithReason : (string, string) => Js.Promise.t(C.t) =
      "setName";
    let setName (:reason=?, name, t) =
      switch (reason) {
      | None => setName(name, t)
      | Some(reason) => setNameWithReason(name, reason, t)
      };
    [@bs.send.pipe : C.t] external setPosition : int => Js.Promise.t(C.t) = "";
    [@bs.send.pipe : C.t]
    external setPositionRelative :
      (int, [@bs.as {json|true|json}] _) => Js.Promise.t(C.t) =
      "";
    [@bs.send.pipe : C.t] external setTopic : string => Js.Promise.t(C.t) = "";
    [@bs.send.pipe : C.t]
    external setTopicWithReason : (string, string) => Js.Promise.t(C.t) =
      "setTopic";
    let setTopic (:reason=?, topic, t) =
      switch (reason) {
      | None => setTopic(topic, t)
      | Some(reason) => setTopicWithReason(topic, reason, t)
      };
  };
  type t = guildChannel;
  include
    Impl(
      {
        type nonrec t = t;
      }
    );
};

module TextChannel = {
  module Impl (C: {type t;}) = {
    include
      GuildChannel.Impl(
        {
          type nonrec t = C.t;
        }
      );
    include
      TextBasedChannel(
        {
          type nonrec t = C.t;
        }
      );
    [@bs.get] external members : C.t => collection(snowflake, guildMember) =
      "";
    [@bs.get] external nsfw : C.t => bool = "";
    [@bs.get] [@bs.return nullable] external topic : C.t => option(string) =
      "";
    [@bs.get] external typing : C.t => bool = "";
    [@bs.get] external typingCount : C.t => int = "";
    [@bs.send] external acknowledge : C.t => Js.Promise.t(C.t) = "";
    [@bs.send.pipe : C.t]
    external fetchMessage : snowflake => Js.Promise.t(message) =
      "";
    [@bs.send]
    external fetchMessages :
      C.t => Js.Promise.t(collection(snowflake, message)) =
      "";
    [@bs.send.pipe : C.t]
    external fetchMessagesWithOptions :
      channelLogsQueryOptions => Js.Promise.t(collection(snowflake, message)) =
      "fetchMessages";
    [@bs.send]
    external fetchPinnedMessages :
      C.t => Js.Promise.t(collection(snowflake, message)) =
      "";
    [@bs.send]
    external fetchWebhooks :
      C.t => Js.Promise.t(collection(snowflake, webhook)) =
      "";
    /*
     .search(options)
     Performs a search within the channel.

     This is only available when using a user account.

     PARAMETER	TYPE	OPTIONAL	DEFAULT	DESCRIPTION
     options	MessageSearchOptions		{}
     Options to pass to the search

     Returns: Promise<MessageSearchResult>
     Examples:
     channel.search({
       content: 'discord.js',
       before: '2016-11-17'
     }).then(res => {
       const hit = res.messages[0].find(m => m.hit).content;
       console.log(`I found: **${hit}**, total results: ${res.totalResults}`);
     }).catch(console.error);
     */
  };
  type t = textChannel;
  include
    Impl(
      {
        type nonrec t = t;
      }
    );
};

module Presence = {
  let encodePresenceStatus (x) =
    switch (x) {
    | Online => "online"
    | Idle => "idle"
    | Invisible => "invisible"
    | DND => "dnd"
    };
};

module User = {
  module Impl (U: {type t;}) = {
    [@bs.get] external avatar : U.t => string = "";
    [@bs.get] external avatarURL : U.t => string = "";
    [@bs.get] external bot : U.t => bool = "";
    [@bs.get] external client : U.t => client = "";
    [@bs.get] external createdAt : U.t => Js.Date.t = "";
    [@bs.get] external createdTimestamp : U.t => float = "";
    [@bs.get] external defaultAvatarURL : U.t => string = "";
    [@bs.get] external discriminator : U.t => string = "";
    [@bs.get] external displayAvatarURL : U.t => string = "";
    [@bs.get] [@bs.return nullable]
    external dmChannel : U.t => option(dmChannel) =
      "";
    [@bs.get] external id : U.t => snowflake = "";
    [@bs.get] external lastMessage : U.t => message = "";
    [@bs.get] external lastMessageID : U.t => snowflake = "";
    [@bs.get] [@bs.return nullable] external note : U.t => option(string) = "";
    [@bs.get] external presence : U.t => presence = "";
    [@bs.get] external tag : U.t => string = "";
    [@bs.get] external username : U.t => string = "";
    [@bs.send] external addFriend : U.t => Js.Promise.t(U.t) = "";
    [@bs.send] external block : U.t => Js.Promise.t(U.t) = "";
    [@bs.send] external createDM : U.t => Js.Promise.t(dmChannel) = "";
    [@bs.send] external deleteDM : U.t => Js.Promise.t(dmChannel) = "";
    [@bs.send] external equals : (U.t, U.t) => bool = "";
    /* fetchProfile(): Promise<UserProfile>, */
    [@bs.send] external removeFriend : U.t => Js.Promise.t(U.t) = "";
    [@bs.send.pipe : U.t] external setNote : string => Js.Promise.t(U.t) = "";
    /* typingDurationIn(channel: ChannelResolvable): number, */
    /* typingIn(channel: ChannelResolvable): boolean, */
    /* typingSinceIn(channel: ChannelResolvable): Date, */
    [@bs.send] external unblock : U.t => Js.Promise.t(U.t) = "";
    include
      UserResolvable(
        {
          type nonrec t = U.t;
        }
      );
  };
  type t = user;
  include
    Impl(
      {
        type nonrec t = t;
      }
    );
};

module ClientUser = {
  module Impl (U: {type t;}) = {
    include
      User.Impl(
        {
          type nonrec t = U.t;
        }
      );
    [@bs.send.pipe : U.t]
    external setPresence :
      Js.t(
        {
          ..
          status: string, /* online, idle, invisible, dnd */
          afk: Js.boolean,
          game: Js.t({.. name: string, url: string})
        }
      ) =>
      Js.Promise.t(U.t) =
      "";
    let setPresence
        (:status=Online, :afk=false, :game="", :gameUrl="", user: U.t) =
      setPresence(
        {
          "status": status |> Presence.encodePresenceStatus,
          "afk": afk |> Js.Boolean.to_js_boolean,
          "game": {"name": game, "url": gameUrl}
        },
        user
      );
  };
  type t = clientUser;
  include
    Impl(
      {
        type nonrec t = t;
      }
    );
  external asUser : t => user = "%identity";
};

module GuildMember = {
  type t = guildMember;
  include
    UserResolvable(
      {
        type nonrec t = t;
      }
    );
  include
    TextBasedChannel(
      {
        type nonrec t = t;
      }
    );
};

module MessageEmbed = {
  type t = messageEmbed;
  [@bs.get] [@bs.return nullable]
  external author : t => option(messageEmbedAuthor) =
    "";
  [@bs.get] external client : t => client = "";
  [@bs.get] external color : t => float = "";
  [@bs.get] external createdAt : t => Js.Date.t = "";
  [@bs.get] external createdTimestamp : t => float = "";
  [@bs.get] [@bs.return nullable] external description : t => option(string) =
    "";
  [@bs.get] external fields : t => array(messageEmbedField) = "";
  [@bs.get] [@bs.return nullable]
  external footer : t => option(messageEmbedFooter) =
    "";
  [@bs.get] external hexColor : t => string = "";
  [@bs.get] [@bs.return nullable]
  external image : t => option(messageEmbedImage) =
    "";
  [@bs.get] external message : t => message = "";
  [@bs.get] [@bs.return nullable]
  external provider : t => option(messageEmbedProvider) =
    "";
  [@bs.get] [@bs.return nullable]
  external thumbnail : t => option(messageEmbedThumbnail) =
    "";
  [@bs.get] [@bs.return nullable] external title : t => option(string) = "";
  [@bs.get] external embedType : t => string = "type";
  [@bs.get] external url : t => string = "";
  [@bs.get] [@bs.return nullable]
  external video : t => option(messageEmbedVideo) =
    "";
  module Author = {
    type t = messageEmbedAuthor;
    [@bs.get] external embed : t => messageEmbed = "";
    [@bs.get] external iconURL : t => string = "";
    [@bs.get] external name : t => string = "";
    [@bs.get] external url : t => string = "";
  };
  module Field = {
    type t = messageEmbedField;
    [@bs.get] external embed : t => messageEmbed = "";
    [@bs.get] external inline : t => bool = "";
    [@bs.get] external name : t => string = "";
    [@bs.get] external value : t => string = "";
  };
  module Footer = {
    type t = messageEmbedFooter;
    [@bs.get] external embed : t => messageEmbed = "";
    [@bs.get] external iconURL : t => string = "";
    [@bs.get] external proxyIconURL : t => string = "";
    [@bs.get] external text : t => string = "";
  };
  module Image = {
    type t = messageEmbedImage;
    [@bs.get] external embed : t => messageEmbed = "";
    [@bs.get] external height : t => int = "";
    [@bs.get] external proxyURL : t => string = "";
    [@bs.get] external url : t => string = "";
    [@bs.get] external width : t => int = "";
  };
  module Provider = {
    type t = messageEmbedProvider;
    [@bs.get] external embed : t => messageEmbed = "";
    [@bs.get] external name : t => string = "";
    [@bs.get] external url : t => string = "";
  };
  module Thumbnail = {
    type t = messageEmbedThumbnail;
    [@bs.get] external embed : t => messageEmbed = "";
    [@bs.get] external height : t => int = "";
    [@bs.get] external proxyURL : t => string = "";
    [@bs.get] external url : t => string = "";
    [@bs.get] external width : t => int = "";
  };
  module Video = {
    type t = messageEmbedVideo;
    [@bs.get] external embed : t => messageEmbed = "";
    [@bs.get] external height : t => int = "";
    [@bs.get] external url : t => string = "";
    [@bs.get] external width : t => int = "";
  };
};

module RichEmbed = {
  type t = richEmbed;
  [@bs.module "discord.js"] [@bs.new] external make : unit => t = "RichEmbed";
  [@bs.send.pipe : t] external setTitle : string => t = "";
  [@bs.send.pipe : t] external setDescription : string => t = "";
  [@bs.send.pipe : t] external setURL : string => t = "";
  [@bs.send.pipe : t] external setColor : colorResolvable => t = "";
  [@bs.send.pipe : t] external setAuthor : (string, string, string) => t = "";
  [@bs.send.pipe : t] external setTimestamp : Js.Date.t => t = "";
  [@bs.send.pipe : t] external setTimestampToNow : unit => t = "setTimestamp";
  [@bs.send.pipe : t] external addField : (string, string) => t = "";
  [@bs.send.pipe : t]
  external addFieldInline : (string, string, [@bs.as {json|true|json}] _) => t =
    "addField";
  [@bs.send] external addBlankField : t => t = "";
  [@bs.send.pipe : t]
  external addBlankFieldInline : ([@bs.as {json|true|json}] _) => t =
    "addField";
  [@bs.send.pipe : t] external setImage : string => t = "";
  [@bs.send.pipe : t] external setFooter : (string, string) => t = "";
};

module ColorResolvable = {
  type t = colorResolvable;
  external ofString : string => t = "%identity";
  external ofFloat : float => t = "%identity";
  external ofInt : int => t = "%identity";
  external rgb : array(int) => t = "%identity";
  let rgb (r, g, b) = [|r, g, b|] |> rgb;
};

module FileOptions = {
  type t = fileOptions;
  type jsFileOptions =
    Js.t(
      {
        .
        attachment: bufferResolvable,
        name:
          Js.undefined(string) /* default: "file.jpg" */
      }
    );
  external ofJsFileOptions : jsFileOptions => t = "%identity";
  let make (:name=?, attachment) : t =
    ofJsFileOptions(
      {"attachment": attachment, "name": Js.Undefined.from_opt(name)}
    );
};

module BufferResolvable = {
  type t = bufferResolvable;
  external ofBuffer : Node.Buffer.t => t = "%identity";
  external ofURL : string => t = "%identity";
  external ofLocalFilepath : string => t = "%identity";
  external ofStream : string => t = "%identity";
};

module SplitOptions = {
  type t = splitOptions;
  let make (:maxLength=?, :char=?, :prepend=?, :append=?, ()) = {
    maxLength,
    char: char |> Utils.Option.value("\n"),
    prepend: prepend |> Utils.Option.value(""),
    append: append |> Utils.Option.value("")
  };
};

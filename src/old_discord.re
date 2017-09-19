type message_t;

type client_t;

type dm_channel_t;

type text_channel_t;

type user_t;

type snowflake = string;

type presenceStatus =
  | Online
  | Idle
  | Invisible
  | DND;

let encodePresenceStatus (x) =
  switch (x) {
  | Online => "online"
  | Idle => "idle"
  | Invisible => "invisible"
  | DND => "dnd"
  };

module Guild = {
  type t;
  /* [@bs.get] external afkChannel: t => Js.Nullable.t(VoiceChannel.t) = ""; */
  [@bs.get] external afkChannelId : t => Js.Nullable.t(string) = "";
  [@bs.get] external afkTimeout : t => Js.Nullable.t(float) = "";
  [@bs.get] external applicationID : t => Js.Nullable.t(snowflake) = "";
  [@bs.get] external available : t => bool = "";
  /* channels: Collection<Snowflake, GuildChannel> */
  [@bs.get] external client : t => client_t = "";
  [@bs.get] external createdAt : t => Js.Date.t = "";
  [@bs.get] external createdTimestamp : t => float = "";
  [@bs.get] external defaultChannel : t => text_channel_t = "";
  /* [@bs.get] external defaultRole : t => role_t = ""; */
  [@bs.get] external embedEnabled : t => bool = "";
  /* emojis: Collection<Snowflake, Emoji> */
  [@bs.get] external explicitContentFilter : t => int = "";
  /* features: Array<Object> */
  [@bs.get] external icon : t => Js.Nullable.t(string) = "";
  [@bs.get] external iconURL : t => Js.Nullable.t(string) = "";
  [@bs.get] external id : t => snowflake = "";
  [@bs.get] external joinedAt : t => Js.Date.t = "";
  [@bs.get] external joinedTimestamp : t => float = "";
  [@bs.get] external large : t => bool = "";
  /* [@bs.get] external me : t => Js.Nullable.t(GuildMember.t) = ""; */
  [@bs.get] external memberCount : t => int = "";
  /* members: Collection<Snowflake, GuildMember> */
  [@bs.get] external name : t => string = "";
  [@bs.get] external nameAcronym : t => string = "";
  /* [@bs.get] external owner : t => GuildMember.t = ""; */
  [@bs.get] external ownerID : t => snowflake = "";
  /* presences: Collection<Snowflake, Presence> */
  [@bs.get] external region : t => string = "";
  /* roles: Collection<Snowflake, Role> */
  [@bs.get] external splash : t => Js.Nullable.t(string) = "";
  [@bs.get] external splashURL : t => Js.Nullable.t(string) = "";
  /* [@bs.get] external systemChannel : t => Js.Nullable.t(GuildChannel.t) = ""; */
  [@bs.get] external systemChannelID : t => Js.Nullable.t(snowflake) = "";
  [@bs.get] external verificationLevel : t => int = "";
  /* [@bs.get] external voiceConnection : t => Js.Nullable.t(VoiceConnection.t) = ""; */
};

module Channel = {
  type t;
  [@bs.get] external client : t => client_t = "";
  [@bs.get] external createdAt : t => Js.Date.t = "";
  [@bs.get] external createdTimestamp : t => float = "";
  [@bs.get] external id : t => snowflake = "";
  /* type: 'dm' | 'group' | 'text' | 'voice', */
  [@bs.get] external channelType : t => string = "type";
  [@bs.send] external delete : t => Js.Promise.t(t) = "";
  external asDMChannel : t => dm_channel_t = "%identity";
  let asDMChannel (channel) =
    switch (channelType(channel)) {
    | "dm" => Some(asDMChannel(channel))
    | _ => None
    };
  external asTextChannel : t => text_channel_t = "%identity";
  let asTextChannel (channel) =
    switch (channelType(channel)) {
    | "text" => Some(asTextChannel(channel))
    | _ => None
    };
};

module DMChannel = {
  type t = dm_channel_t;
  [@bs.get] external client : t => client_t = "";
  [@bs.get] external createdAt : t => Js.Date.t = "";
  [@bs.get] external createdTimestamp : t => float = "";
  [@bs.get] external id : t => snowflake = "";
  [@bs.get] external lastMessageID : t => Js.Nullable.t(snowflake) = "";
  [@bs.get] external recipient : t => user_t = "";
  [@bs.get] external typing : t => bool = "";
  [@bs.get] external typingCount : t => int = "";
  [@bs.send] external delete : t => Js.Promise.t(t) = "";
};

module TextChannel = {
  type t = text_channel_t;
  [@bs.get] external client : t => client_t = "";
  [@bs.get] external createdAt : t => Js.Date.t = "";
  [@bs.get] external createdTimestamp : t => float = "";
  [@bs.get] external deletable : t => bool = "";
  [@bs.get] external guild : t => Guild.t = "";
  [@bs.get] external id : t => snowflake = "";
  [@bs.get] external lastMessageID : t => Js.Nullable.t(snowflake) = "";
  [@bs.get] external name : t => string = "";
  [@bs.get] external nsfw : t => bool = "";
  [@bs.get] external position : t => int = "";
  [@bs.get] external topic : t => Js.Nullable.t(string) = "";
  [@bs.get] external typing : t => bool = "";
  [@bs.get] external typingCount : t => int = "";
};

module User = {
  type t = user_t;
  [@bs.get] external avatar : t => string = "";
  [@bs.get] external avatarURL : t => string = "";
  [@bs.get] external bot : t => bool = "";
  [@bs.get] external client : t => client_t = "";
  [@bs.get] external createdAt : t => Js.Date.t = "";
  [@bs.get] external createdTimestamp : t => float = "";
  [@bs.get] external defaultAvatarURL : t => string = "";
  [@bs.get] external discriminator : t => string = "";
  [@bs.get] external displayAvatarURL : t => string = "";
  /* dmChannel: DMChannel, */
  [@bs.get] external dmChannel : t => Channel.t = "";
  [@bs.get] external id : t => snowflake = "";
  [@bs.get] external lastMessage : t => message_t = "";
  [@bs.get] external lastMessageID : t => snowflake = "";
  [@bs.get] external note : t => string = "";
  /* presence: Presence, */
  [@bs.get] external tag : t => string = "";
  [@bs.get] external username : t => string = "";
  [@bs.send] external addFriend : t => Js.Promise.t(t) = "";
  [@bs.send] external block : t => Js.Promise.t(t) = "";
  /* createDM(): Promise<DMChannel>, */
  [@bs.send] external createDM : t => Js.Promise.t(Channel.t) = "";
  /* deleteDM(): Promise<DMChannel>, */
  [@bs.send] external deleteDM : t => Js.Promise.t(Channel.t) = "";
  [@bs.send] external equals : (t, t) => bool = "";
  /* fetchProfile(): Promise<UserProfile>, */
  [@bs.send] external removeFriend : t => Js.Promise.t(t) = "";
  [@bs.send.pipe : t] external setNote : string => Js.Promise.t(t) = "";
  /* typingDurationIn(channel: ChannelResolvable): number, */
  /* typingIn(channel: ChannelResolvable): boolean, */
  /* typingSinceIn(channel: ChannelResolvable): Date, */
  [@bs.send] external unblock : t => Js.Promise.t(t) = "";
};

module Message = {
  type t = message_t;
  /* attachments: Collection<Snowflake, MessageAttachment>, */
  [@bs.get] external author : t => User.t = "";
  /* channel: TextChannel | DMChannel | GroupDMChannel, */
  [@bs.get] external channel : t => Channel.t = "";
  [@bs.get] external cleanContent : t => string = "";
  [@bs.get] external client : t => client_t = "";
  [@bs.get] external content : t => string = "";
  [@bs.get] external createdAt : t => Js.Date.t = "";
  [@bs.get] external createdTimestamp : t => float = "";
  [@bs.get] external deletable : t => bool = "";
  [@bs.get] external editable : t => bool = "";
  [@bs.get] external editedAt : t => Js.Date.t = "";
  [@bs.get] external editedTimestamp : t => float = "";
  [@bs.get] external edits : t => array(t) = "";
  /* embeds: MessageEmbed[], */
  [@bs.get] external guild : t => Js.Nullable.t(Guild.t) = "";
  [@bs.get] external hit : t => bool = "";
  [@bs.get] external id : t => snowflake = "";
  /* member: GuildMember, */
  /* mentions: MessageMentions, */
  [@bs.get] external nonce : t => string = "";
  [@bs.get] external pinnable : t => bool = "";
  [@bs.get] external pinned : t => bool = "";
  /* reactions: Collection<Snowflake, MessageReaction>, */
  [@bs.get] external system : t => bool = "";
  [@bs.get] external tts : t => bool = "";
  [@bs.get] external messageType : t => string = "";
  [@bs.get] external webhookID : t => snowflake = "";
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
  /* editCode(lang: string, content: StringResolvable): Promise<Message>, */
  /* equals(message: Message, rawData: Object): boolean, */
  /* fetchWebhook(): Promise<Webhook>, */
  /* isMemberMentioned(member: GuildMember | User): boolean, */
  [@bs.send.pipe : t] external isMemberMentioned : User.t => Js.Promise.t(t) =
    "";
  /* isMentioned(data: GuildChannel | User | Role | Snowflake): boolean, */
  [@bs.send.pipe : t] external isUserMentioned : User.t => Js.Promise.t(t) =
    "isMentioned";
  /* [@bs.send] external isChannelMentioned : (t, Channel.t) => Js.Promise.t(bool) = "isMentioned"; */
  /* [@bs.send] external isRoleMentioned : (t, Role.t) => Js.Promise.t(bool) = "isMentioned"; */
  [@bs.send.pipe : t] external isMentioned : snowflake => Js.Promise.t(bool) =
    "";
  [@bs.send] external pin : t => Js.Promise.t(t) = "";
  /* react(emoji: string | Emoji | ReactionEmoji): Promise<MessageReaction>, */
  /* [@bs.send.pipe : t] external react : string => Js.promise.t(MessageReaction.t) = "" */
  /* [@bs.send.pipe : t] external react : Emoji.t => Js.promise.t(MessageReaction.t) = "" */
  /* [@bs.send.pipe : t] external react : ReactionEmoji.t => Js.promise.t(MessageReaction.t) = "" */
  /* reply(
       content?: StringResolvable,
       options?: MessageOptions,
     ): Promise<Message | Message[]>,
     reply(options?: MessageOptions): Promise<Message | Message[]>, */
  type messageOptions = Js.t({. split: Js.boolean});
  [@bs.send.pipe : t]
  external reply : (string, messageOptions) => Js.Promise.t(t) =
    "";
  let reply (:split=false, content: string, message: t) =
    reply(content, {"split": split |> Js.Boolean.to_js_boolean}, message);
  [@bs.send.pipe : t]
  external replyMultiline : (array(string), messageOptions) => Js.Promise.t(t) =
    "reply";
  let replyMultiline (:split=true, content: list(string), message: t) =
    replyMultiline(
      content |> Array.of_list,
      {"split": split |> Js.Boolean.to_js_boolean},
      message
    );
  [@bs.send] external unpin : t => Js.Promise.t(t) = "";
};

module ClientUser = {
  type t;
  [@bs.send.pipe : t]
  external setPresence :
    Js.t(
      {
        ..
        status: string, /* online, idle, invisible, dnd */
        afk: Js.boolean,
        game: Js.t({.. name: string, url: string})
      }
    ) =>
    Js.Promise.t(t) =
    "";
  let setPresence (:status=Online, :afk=false, :game="", :gameUrl="", user: t) =
    setPresence(
      {
        "status": status |> encodePresenceStatus,
        "afk": afk |> Js.Boolean.to_js_boolean,
        "game": {"name": game, "url": gameUrl}
      },
      user
    );
};

module Client = {
  type t = client_t;
  [@bs.module "discord.js"] [@bs.new] external createClient : unit => t =
    "Client";
  [@bs.send] external login : (t, string) => unit = "";
  [@bs.send] external onReady : (t, [@bs.as "ready"] _, unit => unit) => unit =
    "on";
  [@bs.send]
  external onMessage : (t, [@bs.as "message"] _, Message.t => unit) => unit =
    "on";
  [@bs.get] external user : t => ClientUser.t = "";
};

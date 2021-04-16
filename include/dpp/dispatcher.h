#pragma once

#include <dpp/discord.h>
#include <dpp/message.h>
#include <functional>

namespace dpp {

/** @brief Base event parameter struct */
struct event_dispatch_t {
	/** Raw event text */
	std::string raw_event;
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	event_dispatch_t(const std::string& raw);
};

/** @brief Log messages */
struct log_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	log_t(const std::string& raw);
	/** Severity */
	loglevel severity;
	/** Log Message */
	std::string message;
};

/** @brief Voice state update */
struct voice_state_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	voice_state_update_t(const std::string& raw);
	/** Voice state */
	voicestate state;
};

/**
 * @brief Create interaction
 */
struct interaction_create_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	interaction_create_t(const std::string& raw);
	interaction command;
};

/** @brief Delete guild */
struct guild_delete_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_delete_t(const std::string& raw);
	/** Deleted guild */
	guild* deleted;
};

/** @brief Delete channel */
struct channel_delete_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	channel_delete_t(const std::string& raw);
	guild* deleting_guild;
	channel* deleted;
};

/** @brief Update channel */
struct channel_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	channel_update_t(const std::string& raw);
	guild* updating_guild;
	channel* updated;
};

/** @brief Session ready */
struct ready_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	ready_t(const std::string& raw);
	std::string session_id;
	uint32_t shard_id;
};

/** @brief Message Deleted */
struct message_delete_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	message_delete_t(const std::string& raw);
	message* deleted;
};

struct application_command_delete_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	application_command_delete_t(const std::string& raw);
};

/** @brief Guild member remove */
struct guild_member_remove_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_member_remove_t(const std::string& raw);
	guild* removing_guild;
	user* removed;
};

/**
 * @brief Create application slash command
 * 
 */
struct application_command_create_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	application_command_create_t(const std::string& raw);
};

/** @brief Session resumed */
struct resumed_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	resumed_t(const std::string& raw);
	std::string session_id;
	uint32_t shard_id;
};

/** @brief Guild role create */
struct guild_role_create_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_role_create_t(const std::string& raw);
	guild* creating_guild;
	role* created;
};

/** @brief Typing start */
struct typing_start_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	typing_start_t(const std::string& raw);
	guild* typing_guild;
	channel* typing_channel;
	user* typing_user;
	time_t timestamp;
};

/** @brief Message reaction add */
struct message_reaction_add_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	message_reaction_add_t(const std::string& raw);
	guild* reacting_guild;
	user* reacting_user;
	channel* reacting_channel;
	emoji* reacting_emoji;
	snowflake message_id;
};

/** @brief Guild members chunk */
struct guild_members_chunk_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_members_chunk_t(const std::string& raw);
	guild* adding;
	guild_member_map* members;
};

/** @brief Message reaction remove */
struct message_reaction_remove_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	message_reaction_remove_t(const std::string& raw);
        guild* reacting_guild;
        user* reacting_user;
        channel* reacting_channel;
        emoji* reacting_emoji;
        snowflake message_id;
};

/** @brief Create guild */
struct guild_create_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_create_t(const std::string& raw);
	guild* created;
};

/** @brief Create channel */
struct channel_create_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	channel_create_t(const std::string& raw);
	guild* creating_guild;
	channel* created;
};

/** @brief Message remove emoji */
struct message_reaction_remove_emoji_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	message_reaction_remove_emoji_t(const std::string& raw);
        guild* reacting_guild;
        channel* reacting_channel;
        emoji* reacting_emoji;
        snowflake message_id;
};

/** @brief Message delete bulk */
struct message_delete_bulk_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	message_delete_bulk_t(const std::string& raw);
	guild* deleting_guild;
	user* deleting_user;
	channel* deleting_channel;
	std::vector<snowflake> deleted;
};

/** @brief Guild role update */
struct guild_role_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_role_update_t(const std::string& raw);
	guild* updating_guild;
	role* updated;
};

/** @brief Guild role delete */
struct guild_role_delete_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_role_delete_t(const std::string& raw);
	guild* deleting_guild;
	role* deleted;
};

/** @brief Channel pins update */
struct channel_pins_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	channel_pins_update_t(const std::string& raw);
	guild* pin_guild;
	channel* pin_channel;
	time_t timestamp;
};

/** @brief Message remove all reactions */
struct message_reaction_remove_all_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	message_reaction_remove_all_t(const std::string& raw);
        guild* reacting_guild;
        channel* reacting_channel;
        snowflake message_id;
};

/** @brief Voice server update */
struct voice_server_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	voice_server_update_t(const std::string& raw);
	snowflake guild_id;
	std::string token;
	std::string endpoint;
};

/** @brief Guild emojis update */
struct guild_emojis_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_emojis_update_t(const std::string& raw);
	std::vector<snowflake> emojis;
	guild* updating_guild;
};

/**
 * @brief Presence update
 * 
 */
struct presence_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	presence_update_t(const std::string& raw);
	presence rich_presence;
};

/** @brief Webhooks update */
struct webhooks_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	webhooks_update_t(const std::string& raw);
	guild* webhook_guild;
	channel* webhook_channel;
};

/** @brief Guild member add */
struct guild_member_add_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_member_add_t(const std::string& raw);
	guild* adding_guild;
	guild_member* added;
};

/** @brief Invite delete */
struct invite_delete_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	invite_delete_t(const std::string& raw);
	invite deleted_invite;
};

/** @brief Guild update */
struct guild_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_update_t(const std::string& raw);
	guild* updated;
};

/** @brief Guild integrations update */
struct guild_integrations_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_integrations_update_t(const std::string& raw);
	guild* updating_guild;
};

/** @brief Guild member update */
struct guild_member_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_member_update_t(const std::string& raw);
	guild* updating_guild;
	guild_member* updated;
};

/**
 * @brief Update application slash command
 * 
 */
struct application_command_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	application_command_update_t(const std::string& raw);
};

/** @brief Invite create */
struct invite_create_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	invite_create_t(const std::string& raw);
	invite created_invite;
};

/** @brief Message update */
struct message_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	message_update_t(const std::string& raw);
	message* updated;
};

/* @brief User update */
struct user_update_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	user_update_t(const std::string& raw);
	user* updated;
};

/** @brief Create message */
struct message_create_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	message_create_t(const std::string& raw);
	message* msg;
};

/** @brief Guild ban add */
struct guild_ban_add_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_ban_add_t(const std::string& raw);
	guild* banning_guild;
	user banned;
};

/** @brief Guild ban remove */
struct guild_ban_remove_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	guild_ban_remove_t(const std::string& raw);
	guild* unbanning_guild;
	user unbanned;
};

/** @brief Integration create */
struct integration_create_t : public event_dispatch_t {
	/** Constructor
	 * @param raw Raw event text as JSON
	 */
	integration_create_t(const std::string& raw);
	integration created_integration;
};

/** @brief Integration update */
struct integration_update_t : public event_dispatch_t {
	/** 
	 * @brief Constructor
	 * @param raw Raw event text as JSON
	 */
	integration_update_t(const std::string& raw);
	integration updated_integration;
};

/** @brief Integration delete */
struct integration_delete_t : public event_dispatch_t {
	/** 
	 * @brief Constructor
	 * @param raw Raw event text as JSON
	 */
	integration_delete_t(const std::string& raw);
	integration deleted_integration;
};

/** @brief voice buffer send */
struct voice_buffer_send_t : public event_dispatch_t {
	/** 
	 * @brief Constructor
	 * @param raw Raw event text as JSON
	 */
	voice_buffer_send_t(const std::string &raw);
	class DiscordVoiceClient* voice_client;
	int buffer_size;
};

/** @brief voice user talking */
struct voice_user_talking_t : public event_dispatch_t {
	/** 
	 * @brief Constructor
	 * @param raw Raw event text as JSON
	 */
	voice_user_talking_t(const std::string &raw);
	class DiscordVoiceClient* voice_client;
	snowflake user_id;
	uint8_t talking_flags;
};

/** @brief voice user talking */
struct voice_ready_t : public event_dispatch_t {
	/** 
	 * @brief Constructor
	 * @param raw Raw event text as JSON
	 */
	voice_ready_t(const std::string &raw);
	class DiscordVoiceClient* voice_client;
};

/** @brief voice receive packet */
struct voice_receive_t : public event_dispatch_t {
	/** 
	 * @brief Constructor
	 * @param raw Raw event text as JSON
	 */
	voice_receive_t(const std::string &raw);
	class DiscordVoiceClient* voice_client;
	uint8_t* audio;
	size_t audio_size;
};

/** @brief The dispatcher class contains a set of std::functions representing hooked events
 * that the user code is interested in. These are modified via the on_eventname style
 * methods in the cluster class.
 */
class dispatcher {
public:
	/** @brief Event handler function pointer for log event
	 * @param event Event parameters
	 */
	std::function<void(const log_t& event)> log;
	/** @brief Event handler function pointer for voice state update event
	 * @param event Event parameters
	 */
	std::function<void(const voice_state_update_t& event)> voice_state_update;
	/** @brief Event handler function pointer for interaction create event
	 * @param event Event parameters
	 */
	std::function<void(const interaction_create_t& event)> interaction_create;
	/** @brief Event handler function pointer for guild delete event
	 * @param event Event parameters
	 */
	std::function<void(const guild_delete_t& event)> guild_delete;
	/** @brief Event handler function pointer for channel delete event
	 * @param event Event parameters
	 */
	std::function<void(const channel_delete_t& event)> channel_delete;
	/** @brief Event handler function pointer for channel update event
	 * @param event Event parameters
	 */
	std::function<void(const channel_update_t& event)> channel_update;
	/** @brief Event handler function pointer for ready event
	 * @param event Event parameters
	 */
	std::function<void(const ready_t& event)> ready;
	/** @brief Event handler function pointer for message delete event
	 * @param event Event parameters
	 */
	std::function<void(const message_delete_t& event)> message_delete;
	/** @brief Event handler function pointer for application command delete event
	 * @param event Event parameters
	 */
	std::function<void(const application_command_delete_t& event)> application_command_delete;
	/** @brief Event handler function pointer for guild member remove event
	 * @param event Event parameters
	 */
	std::function<void(const guild_member_remove_t& event)> guild_member_remove;
	/** @brief Event handler function pointer for guild member remove event
	 * @param event Event parameters
	 */
	std::function<void(const application_command_create_t& event)> application_command_create;
	/** @brief Event handler function pointer for resumed event
	 * @param event Event parameters
	 */
	std::function<void(const resumed_t& event)> resumed;
	/** @brief Event handler function pointer for guild role create event
	 * @param event Event parameters
	 */
	std::function<void(const guild_role_create_t& event)> guild_role_create;
	/** @brief Event handler function pointer for typing start event
	 * @param event Event parameters
	 */
	std::function<void(const typing_start_t& event)> typing_start;
	/** @brief Event handler function pointer for message reaction add event
	 * @param event Event parameters
	 */
	std::function<void(const message_reaction_add_t& event)> message_reaction_add;
	/** @brief Event handler function pointer for guild members chunk event
	 * @param event Event parameters
	 */
	std::function<void(const guild_members_chunk_t& event)> guild_members_chunk;
	/** @brief Event handler function pointer for message reaction remove event
	 * @param event Event parameters
	 */
	std::function<void(const message_reaction_remove_t& event)> message_reaction_remove;
	/** @brief Event handler function pointer for guild create event
	 * @param event Event parameters
	 */
	std::function<void(const guild_create_t& event)> guild_create;
	/** @brief Event handler function pointer for guild channel create event
	 * @param event Event parameters
	 */
	std::function<void(const channel_create_t& event)> channel_create;
	/** @brief Event handler function pointer for message reaction remove emoji event
	 * @param event Event parameters
	 */
	std::function<void(const message_reaction_remove_emoji_t& event)> message_reaction_remove_emoji;
	/** @brief Event handler function pointer for message delete bulk event
	 * @param event Event parameters
	 */
	std::function<void(const message_delete_bulk_t& event)> message_delete_bulk;
	/** @brief Event handler function pointer for guild role update event
	 * @param event Event parameters
	 */
	std::function<void(const guild_role_update_t& event)> guild_role_update;
	/** @brief Event handler function pointer for guild role delete event
	 * @param event Event parameters
	 */
	std::function<void(const guild_role_delete_t& event)> guild_role_delete;
	/** @brief Event handler function pointer for channel pins update event
	 * @param event Event parameters
	 */
	std::function<void(const channel_pins_update_t& event)> channel_pins_update;
	/** @brief Event handler function pointer for message reaction remove all event
	 * @param event Event parameters
	 */
	std::function<void(const message_reaction_remove_all_t& event)> message_reaction_remove_all;
	/** @brief Event handler function pointer for voice server update event
	 * @param event Event parameters
	 */
	std::function<void(const voice_server_update_t& event)> voice_server_update;
	/** @brief Event handler function pointer for guild emojis update event
	 * @param event Event parameters
	 */
	std::function<void(const guild_emojis_update_t& event)> guild_emojis_update;
	/** @brief Event handler function pointer for presence update event
	 * @param event Event parameters
	 */
	std::function<void(const presence_update_t& event)> presence_update;
	/** @brief Event handler function pointer for webhooks update event
	 * @param event Event parameters
	 */
	std::function<void(const webhooks_update_t& event)> webhooks_update;
	/** @brief Event handler function pointer for guild member add event
	 * @param event Event parameters
	 */
	std::function<void(const guild_member_add_t& event)> guild_member_add;
	/** @brief Event handler function pointer for invite delete event
	 * @param event Event parameters
	 */
	std::function<void(const invite_delete_t& event)> invite_delete;
	/** @brief Event handler function pointer for guild update event
	 * @param event Event parameters
	 */
	std::function<void(const guild_update_t& event)> guild_update;
	/** @brief Event handler function pointer for guild integrations update event
	 * @param event Event parameters
	 */
	std::function<void(const guild_integrations_update_t& event)> guild_integrations_update;
	/** @brief Event handler function pointer for guild member update event
	 * @param event Event parameters
	 */
	std::function<void(const guild_member_update_t& event)> guild_member_update;
	/** @brief Event handler function pointer for application command update event
	 * @param event Event parameters
	 */
	std::function<void(const application_command_update_t& event)> application_command_update;
	/** @brief Event handler function pointer for invite create event
	 * @param event Event parameters
	 */
	std::function<void(const invite_create_t& event)> invite_create;
	/** @brief Event handler function pointer for message update event
	 * @param event Event parameters
	 */
	std::function<void(const message_update_t& event)> message_update;
	/** @brief Event handler function pointer for user update event
	 * @param event Event parameters
	 */
	std::function<void(const user_update_t& event)> user_update;
	/** @brief Event handler function pointer for message create event
	 * @param event Event parameters
	 */
	std::function<void(const message_create_t& event)> message_create;
	/** @brief Event handler function pointer for guild ban add event
	 * @param event Event parameters
	 */
	std::function<void(const guild_ban_add_t& event)> guild_ban_add;
	/** @brief Event handler function pointer for guild ban remove event
	 * @param event Event parameters
	 */
	std::function<void(const guild_ban_remove_t& event)> guild_ban_remove;
	/** @brief Event handler function pointer for integration create event
	 * @param event Event parameters
	 */
	std::function<void(const integration_create_t& event)> integration_create;
	/** @brief Event handler function pointer for integration update event
	 * @param event Event parameters
	 */
	std::function<void(const integration_update_t& event)> integration_update;
	/** @brief Event handler function pointer for integration delete event
	 * @param event Event parameters
	 */
	std::function<void(const integration_delete_t& event)> integration_delete;
	/** @brief Event handler function pointer for voice buffer send event
	 * @param event Event parameters
	 */
	std::function<void(const voice_buffer_send_t& event)> voice_buffer_send;
	/** @brief Event handler function pointer for voice user talking event
	 * @param event Event parameters
	 */
	std::function<void(const voice_user_talking_t& event)> voice_user_talking;
	/** @brief Event handler function pointer for voice ready event
	 * @param event Event parameters
	 */
	std::function<void(const voice_ready_t& event)> voice_ready;
	/** @brief Event handler function pointer for voice receieve event
	 * @param event Event parameters
	 */
	std::function<void(const voice_receive_t& event)> voice_receive;
};

};


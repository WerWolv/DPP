#include <string>
#include <iostream>
#include <fstream>
#include <dpp/discordclient.h>
#include <dpp/discord.h>
#include <dpp/cache.h>
#include <dpp/stringops.h>
#include <spdlog/spdlog.h>


std::map<std::string, dpp::guild_flags> featuremap = {
	{"INVITE_SPLASH", dpp::g_invite_splash },
	{"VIP_REGIONS", dpp::g_vip_regions },
	{"VANITY_URL", dpp::g_vanity_url },
	{"VERIFIED", dpp::g_verified },
	{"PARTNERED", dpp::g_partnered },
	{"COMMUNITY", dpp::g_community },
	{"COMMERCE", dpp::g_commerce },
	{"NEWS", dpp::g_news },
	{"DISCOVERABLE", dpp::g_discoverable },
	{"FEATUREABLE", dpp::g_featureable },
	{"ANIMATED_ICON", dpp::g_animated_icon },
	{"BANNER", dpp::g_banner },
	{"WELCOME_SCREEN_ENABLED", dpp::g_welcome_screen_enabled },
	{"MEMBER_VERIFICATION_GATE_ENABLED", dpp::g_member_verification_gate },
	{"PREVIEW_ENABLED", dpp::g_preview_enabled }
};

std::map<std::string, dpp::region> regionmap = {
        { "brazil", dpp::r_brazil },
        { "central-europe", dpp::r_central_europe },
        { "hong-kong", dpp::r_hong_kong },
        { "india", dpp::r_india },
        { "japan",  dpp::r_japan },
        { "russia", dpp::r_russia },
        { "singapore", dpp::r_singapore },
        { "south-africa", dpp::r_south_africa },
        { "sydney", dpp::r_sydney },
        { "us-central", dpp::r_us_central },
        { "us-east", dpp::r_us_east },
        { "us-south", dpp::r_us_south },
        { "us-west", dpp::r_us_west },
        { "western-europe", dpp::r_western_europe }
};

uint64_t SnowflakeNotNull(json& j, const char *keyname)
{
	return j.find(keyname) != j.end() && !j[keyname].is_null() ? from_string<uint64_t>(j[keyname].get<std::string>(), std::dec) : 0;
}

std::string StringNotNull(json& j, const char *keyname)
{
	return j.find(keyname) != j.end() && !j[keyname].is_null() ? j[keyname].get<std::string>() : "";
}

uint32_t Int32NotNull(json& j, const char *keyname)
{
	return j.find(keyname) != j.end() && !j[keyname].is_null() ? j[keyname].get<uint32_t>() : 0;
}

uint16_t Int16NotNull(json& j, const char *keyname)
{
	return j.find(keyname) != j.end() && !j[keyname].is_null() ? j[keyname].get<uint16_t>() : 0;
}

uint8_t Int8NotNull(json& j, const char *keyname)
{
	return j.find(keyname) != j.end() && !j[keyname].is_null() ? j[keyname].get<uint8_t>() : 0;
}

bool BoolNotNull(json &j, const char *keyname)
{
	return (j.find(keyname) != j.end() && j[keyname].get<bool>() == true);
}

std::map<std::string, std::function<void(DiscordClient* client, json &j)>> events = {
	{
		"READY",
		[](DiscordClient* client, json &j) {
			client->logger->info("Shard {}/{} ready!", client->shard_id, client->max_shards);
			client->sessionid = j["d"]["session_id"];
		}
	},
	{
		"RESUMED",
		[](DiscordClient* client, json &j) {
			client->logger->debug("Successfully resumed session id {}", client->sessionid);
		}
	},
	{
		"GUILD_CREATE",
		[](DiscordClient* client, json &j) {
			dpp::guild* g = new dpp::guild();
			json& d = j["d"];

			g->id = SnowflakeNotNull(d, "id");
			if (d.find("unavailable") == d.end() || d["unavailable"].get<bool>() == false) {
				g->name = StringNotNull(d, "name");
				g->icon = StringNotNull(d, "icon");
				g->discovery_splash = StringNotNull(d, "discovery_splash");
				g->owner_id = SnowflakeNotNull(d, "owner_id");
				if (!d["region"].is_null()) {
					auto r = regionmap.find(d["region"].get<std::string>());
					if (r != regionmap.end()) {
						g->voice_region = r->second;
					}
				}

				g->flags |= BoolNotNull(d, "large") ? dpp::g_large : 0;
				g->flags |= BoolNotNull(d, "widget_enabled") ? dpp::g_widget_enabled : 0;

				for (auto & feature : d["features"]) {
					auto f = featuremap.find(feature.get<std::string>());
					if (f != featuremap.end()) {
						g->flags |= f->second;
					}
				}
				uint8_t scf = Int8NotNull(d, "system_channel_flags");
				if (scf & 1) {
					g->flags |= dpp::g_no_join_notifications;
				}
				if (scf & 2) {
					g->flags |= dpp::g_no_boost_notifications;
				}

				g->afk_channel_id = SnowflakeNotNull(d, "afk_channel_id");
				g->afk_timeout = Int16NotNull(d, "afk_timeout");
				g->widget_channel_id = SnowflakeNotNull(d, "widget_channel_id");
				g->verification_level = Int8NotNull(d, "verification_level");
				g->default_message_notifications = Int8NotNull(d, "default_message_notifications");
				g->explicit_content_filter = Int8NotNull(d, "explicit_content_filter");
				g->mfa_level = Int8NotNull(d, "mfa_level");
				g->application_id = SnowflakeNotNull(d, "application_id");
				g->system_channel_id = SnowflakeNotNull(d, "system_channel_id");
				g->rules_channel_id = SnowflakeNotNull(d, "rules_channel_id");
				//g->joined_at = 
				g->member_count = Int32NotNull(d, "member_count");
				g->vanity_url_code = StringNotNull(d, "vanity_url_code");
				g->description = StringNotNull(d, "description");
				g->banner = StringNotNull(d, "banner");
				g->premium_tier = Int8NotNull(d, "premium_tier");
				g->premium_subscription_count = Int16NotNull(d, "premium_subscription_count");
				g->public_updates_channel_id = SnowflakeNotNull(d, "public_updates_channel_id");
				g->max_video_channel_users = Int32NotNull(d, "max_video_channel_users");

				/* Store guild roles */
				//std::vector<snowflake> roles;

				// Store guild channels
				for (auto & channel : d["channels"]) {
					dpp::channel *c = new dpp::channel();

					c->id = SnowflakeNotNull(channel, "id");
					c->guild_id = SnowflakeNotNull(channel, "guild_id");
					c->position = Int16NotNull(channel, "position");
					c->name = StringNotNull(channel, "name");
					c->topic = StringNotNull(channel, "topic");
					c->last_message_id = SnowflakeNotNull(channel, "last_message_id");
					c->user_limit = Int32NotNull(channel, "user_limit");
					c->rate_limit_per_user = Int16NotNull(channel, "rate_limit_per_user");
					c->owner_id = SnowflakeNotNull(channel, "owner_id");
					c->parent_id = SnowflakeNotNull(channel, "parent_id");
					//c->last_pin_timestamp
					uint8_t type = Int8NotNull(channel, "type");
					c->flags |= BoolNotNull(channel, "nsfw") ? dpp::c_nsfw : 0;
					c->flags |= (type == GUILD_TEXT) ? dpp::c_text : 0;
					c->flags |= (type == GUILD_VOICE) ? dpp::c_voice : 0;
					c->flags |= (type == DM) ? dpp::c_dm : 0;
					c->flags |= (type == GROUP_DM) ? (dpp::c_group | dpp::c_dm) : 0;
					c->flags |= (type == GUILD_CATEGORY) ? dpp::c_category : 0;
					c->flags |= (type == GUILD_NEWS) ? dpp::c_news : 0;
					c->flags |= (type == GUILD_STORE) ? dpp::c_store : 0;

					dpp::store_channel(c);
					g->channels.push_back(c->id);
				}

				//std::map<snowflake, class guild_member*> members;

			} else {
				g->flags |= dpp::g_unavailable;
			}
			dpp::store_guild(g);
		}
	},
	{
		"MESSAGE_UPDATE",
		[](DiscordClient* client, json &j) {
			 client->logger->debug("MESSAGE_UPDATE");
		}
	},
	{
		"MESSAGE_DELETE",
		[](DiscordClient* client, json &j) {
			 client->logger->debug("MESSAGE_DELETE");
		}
	},
	{
		"MESSAGE_CREATE",
		[](DiscordClient* client, json &j) {
			 client->logger->debug("MESSAGE_CREATE");
		}
	},
	{
		"CHANNEL_UPDATE",
		[](DiscordClient* client, json &j) {
			 client->logger->debug("CHANNEL_UPDATE");
		}
	},
	{
		"GUILD_ROLE_UPDATE",
		[](DiscordClient* client, json &j) {
			 client->logger->debug("GUILD_ROLE_UPDATE");
		}
	},
	{
		"MESSAGE_DELETE_BULK",
		[](DiscordClient* client, json &j) {
			 client->logger->debug("MESSAGE_DELETE_BULK");
		}
	},
	{
		"CHANNEL_CREATE",
		[](DiscordClient* client, json &j) {
			 client->logger->debug("CHANNEL_CREATE");
		}
	},
	{
		"CHANNEL_DELETE",
		[](DiscordClient* client, json &j) {
			 client->logger->debug("CHANNEL_DELETE");
		}
	},

};

void DiscordClient::HandleEvent(const std::string &event, json &j)
{
	auto ev_iter = events.find(event);
	if (ev_iter != events.end()) {
		ev_iter->second(this, j);
	} else {
		logger->debug("Unhamdled event: {}", event);
	}
}
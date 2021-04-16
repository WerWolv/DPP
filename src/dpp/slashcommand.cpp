#include <dpp/slashcommand.h>
#include <dpp/discordevents.h>
#include <dpp/discord.h>
#include <nlohmann/json.hpp>

namespace dpp {

using json = nlohmann::json;

slashcommand::slashcommand() : managed() 
{
}

slashcommand::~slashcommand() {
}



slashcommand& slashcommand::fill_from_json(nlohmann::json* j) {
	id = SnowflakeNotNull(j, "id");
	return *this;
}

std::string slashcommand::build_json(bool with_id) const {
	json j;
	if (with_id) {
		j["id"] = std::to_string(id);
	}
	j["name"] = name;
	j["description"] = description;
	if (options.size()) {
		j["options"] = json();
		json& o = j["options"];
		for (auto & opt : options) {
			json n;
			n["name"] = opt.name;
			n["description"] = opt.description;
			n["type"] = opt.type;
			n["required"] = opt.required;

			if (opt.choices.size()) {
				n["choices"] = json();
				json &c = n["choices"];
				for (auto & choice : opt.choices) {
					json t;
					t["name"] = choice.name;
					if (std::holds_alternative<int>(choice.value)) {
						t["value"] = std::get<int>(choice.value);
					} else {
						t["value"] = std::get<std::string>(choice.value);
					}
					c.push_back(t);
				}
			}

			if (opt.options.size()) {
				n["options"] = json();
				json &c = n["options"];
				for (auto & subcommand : opt.options) {
					json o;
					o["name"] = opt.name;
					o["description"] = opt.description;
					o["type"] = opt.type;
					o["required"] = opt.required;
					if (opt.choices.size()) {
						o["choices"] = json();
						json &v = o["choices"];
						for (auto & choice : opt.choices) {
							v["name"] = choice.name;
							if (std::holds_alternative<int>(choice.value)) {
								v["value"] = std::get<int>(choice.value);
							} else {
								v["value"] = std::get<std::string>(choice.value);
							}
						}
						v.push_back(o);
					}
					c.push_back(n);
				}
			}
			o.push_back(n);
		}
	}
	return j.dump();
}

slashcommand& slashcommand::set_name(const std::string &n) {
	name = n;
	return *this;
}

slashcommand& slashcommand::set_description(const std::string &d) {
	description = d;
	return *this;
}

slashcommand& slashcommand::set_application_id(snowflake i) {
	application_id = i;
	return *this;
}

command_option_choice::command_option_choice(const std::string &n, std::variant<std::string, int32_t> v) : name(n), value(v)
{
}

command_option::command_option(command_option_type t, const std::string &n, const std::string &d, bool r) :
	type(t), name(n), description(d), required(r)
{
}

command_option& command_option::add_choice(const command_option_choice &o)
{
	choices.push_back(o);
	return *this;
}

command_option& command_option::add_option(const command_option &o)
{
	options.push_back(o);
	return *this;
}

slashcommand& slashcommand::add_option(const command_option &o)
{
	options.push_back(o);
	return *this;
}

interaction& interaction::fill_from_json(nlohmann::json* j) {
	id = SnowflakeNotNull(j, "id");
	application_id = SnowflakeNotNull(j, "application_id");
	channel_id = SnowflakeNotNull(j, "channel_id");
	guild_id = SnowflakeNotNull(j, "guild_id");
	token = StringNotNull(j, "token");
	type = Int8NotNull(j, "type");
	version = Int8NotNull(j, "version");
	if (j->find("member") != j->end()) {
		json& m = (*j)["member"];
		member = guild_member().fill_from_json(&m, nullptr, nullptr);
		usr = user().fill_from_json(&(m["user"]));
	}
	if (j->find("user") != j->end()) {
		usr = user().fill_from_json(&((*j)["user"]));
	}
	if (j->find("data") != j->end()) {
		json& param = (*j)["data"];
		command_interaction ci;
		ci.id = SnowflakeNotNull(&param, "id");
		ci.name = StringNotNull(&param, "name");
		//ci.resolved = BoolNotNull(&param, "resolved");
		if (param.find("options") != param.end()) {
			for (auto &opt : param["options"]) {
				command_data_option cdo;
				cdo.name = StringNotNull(&opt, "name");
				cdo.type = (command_option_type)Int8NotNull(&opt, "type");
				switch (cdo.type) {
					case co_boolean:
						cdo.value = BoolNotNull(&opt, "value");
					break;
					case co_channel:
					case co_role:
					case co_user:
						cdo.value = SnowflakeNotNull(&opt, "value");
					break;
					case co_integer:
						cdo.value = Int32NotNull(&opt, "value");
					break;
					case co_string:
						cdo.value = StringNotNull(&opt, "value");
					break;
				}
				ci.options.push_back(cdo);
			}
		}
		data = ci;
	}
	return *this;
}

std::string interaction::build_json(bool with_id) const {
	return "";
}

interaction_response::interaction_response() {
	msg = new message();
}

interaction_response::~interaction_response() {
	delete msg;
}

interaction_response& interaction_response::fill_from_json(nlohmann::json* j) {
	type = (interaction_response_type)Int8NotNull(j, "type");
	if (j->find("data") != j->end()) {
		msg->fill_from_json(&((*j)["data"]));
	}
	return *this;
}

std::string interaction_response::build_json() const {
	json j;
	json msg_json = json::parse(msg->build_json());
	j["type"] = this->type;
	j["data"] = msg_json;
	return j.dump();
}


};


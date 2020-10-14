module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <pugixml.hpp>
export module Logger;

import StaticFactory;
import Serialization;

using namespace std::string_literals;

export class Logger
{
public:
	//https://stackoverflow.com/questions/4874128/what-information-to-include-at-each-log-level?noredirect=1&lq=1
	enum class Verbosity
	{
		/*Used to log an error the application cannot recover from, which might lead
		to an immediate program termination.*/
		Critical = 0,
		/*Denotes an often unrecoverable error. Such as failing to open a database
		connection.*/
		Error,
		/*Warns of errors that can be recovered.Such as failing to parse a date or
		using an unsafe routine.*/
		Warning,
		/*General application flow, such as "Starting app", "connecting to db",
		"registering ...". In short, information which should help any observer
		understand what the application is doing in general.*/
		Info,
		/* Information to primary help you to debug your program. E.g., log every
		time a batching routine empties its batch or a new file is created on disk
		etc.*/
		Debug,
		/*The finest logging level. Can be used to log very specific information
		that is only relevant in a true debugging scenario, e.g., log every database
		access or every HTTP call etc.*/
		Trace
	};
	class Channel : public StaticFactory<Channel>
	{
	public:
		//Rule of 5
		virtual ~Channel() = default;
		virtual void write(const std::string& message) = 0;
		//Serializable
		virtual void load(const pugi::xml_node& source) = 0;
		//Cloneable
		[[nodiscard]] virtual std::unique_ptr<Channel> clone() const = 0;
		//Active
		constexpr void activate(bool value = true) { _active = value; };
		[[nodiscard]] constexpr bool active() const { return _active; };
	private:
		bool _active = true;
	};
	//Logging
	constexpr void set_verbosity(const Logger::Verbosity value) { _verbosity = value; };
	void log(const std::string & name, const Logger::Verbosity verbosity, const std::string & message);
	//std::unique_ptr<TimedMessage> time(const std::string & channel, Verbosity verbosity, const std::string& message);
	//Channels
	[[nodiscard]] std::shared_ptr<Channel> find(const std::string& name);
	void add(const std::string& name, std::shared_ptr<Channel> channel);
	//Serializable
	void load(const std::filesystem::path& path);
private:
	Verbosity _verbosity = Verbosity::Trace;
	std::ofstream _file{ "output.txt" };
	std::unique_ptr<Channel> _prototype;
	std::map<std::string, std::shared_ptr<Channel>> _channels;
};
#include <fstream>
#include <map>
#include <pugixml.hpp>
import Logger;
import Terminal;

std::map<std::string, std::shared_ptr<Logger::Channel>> StaticFactory<Logger::Channel>::_prototypes
{
	{"terminal", std::make_shared<Terminal>() }
};

void Logger::log(const std::string & name, const Logger::Verbosity verbosity, const std::string& message)
{
	if (verbosity <= _verbosity)
	{
		auto channel = get(name);
		if (channel->active())
			channel->write(message);
	}
	_file << message;
}

std::shared_ptr<Logger::Channel> Logger::find(const std::string & name) const
{
	const auto match = _channels.find(name);
	return match == _channels.end() ? nullptr : match->second;
}

std::shared_ptr<Logger::Channel> Logger::get(const std::string& name)
{
	const auto channel = find(name);
	return channel ? channel : add(name, _prototype->clone());
}

std::shared_ptr<Logger::Channel> Logger::add(const std::string & name, std::shared_ptr<Logger::Channel> channel)
{
	return _channels[name] = channel;
}

void Logger::load(const std::filesystem::path & path)
{
	pugi::xml_document doc;
	doc.load_file(path.c_str());
	auto source = doc.child("logger");

	set_verbosity(static_cast<Verbosity>(source.attribute("verbosity").as_int()));

	//prototype channel
	const auto prototype = source.child("prototype").first_child();
	_prototype = Channel::create(prototype.name());
	_prototype->load(prototype);

	//other channels
	const auto channels = source.child("channels");
	for (const auto & node : channels)
	{
		std::shared_ptr<Channel> channel = Channel::create(node.name());
		channel->load(node);
		add(node.attribute("name").as_string(), channel);
	}
}

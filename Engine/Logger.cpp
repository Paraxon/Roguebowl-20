import Logger;
#include <fstream>

void Logger::log(const std::string & name, const Logger::Verbosity verbosity, const std::string& message)
{
	if (verbosity <= _verbosity)
	{
		auto channel = find(name);
		if (channel && channel->active())
			channel->write(message);
	}
	_file << message;
}

std::shared_ptr<Logger::Channel> Logger::find(const std::string & name)
{
	return _channels[name];
}

void Logger::add(const std::string & name, std::shared_ptr<Logger::Channel> channel)
{
	_channels[name] = channel;
}
module;
#include <memory>
#include <chrono>
#include <vector>
export module CommandSequence;

import Command;

export class CommandSequence : public Command<bool>
{
public:
	template <typename iter_type>
	CommandSequence(const iter_type& first, const iter_type& last, const std::chrono::duration<float>& limit)
		: _commands(first, last), _timeLimit(limit) {};
	//Command
	void update(TimeStep timestep) override;
protected:
	//Command
	[[nodiscard]] bool poll() const override;
private:
	[[nodiscard]] bool is_complete() const;
	[[nodiscard]] bool is_expired() const;
	[[nodiscard]] std::shared_ptr<Command<bool>> current() const;
	int _index = 0;
	std::chrono::duration<float> _timeLimit, _elapsedTime{};
	std::vector<std::shared_ptr<Command<bool>>> _commands;
	void advance();
	void reset();
};

bool CommandSequence::is_complete() const
{
	return _index >= _commands.size();
}

bool CommandSequence::is_expired() const
{
	return _elapsedTime > _timeLimit;
}

std::shared_ptr<Command<bool>> CommandSequence::current() const
{
	return _commands[std::min(_index, (int)_commands.size() - 1)];
}

void CommandSequence::update(TimeStep timestep)
{
	_elapsedTime += timestep.scaled_time();
	current()->update(timestep);
	Command<bool>::update(timestep);

	if (is_complete() || is_expired())
		reset();
	else if (current()->get_value())
		advance();
}

bool CommandSequence::poll() const
{
	return is_complete();
}

void CommandSequence::advance()
{
	++_index;
	_elapsedTime = std::chrono::seconds::zero();
}

void CommandSequence::reset()
{
	_index = 0;
	_elapsedTime = std::chrono::seconds::zero();
}
module;
#include <memory>
#include <chrono>
#include <vector>
#include <iterator>
export module CommandSequence;

import Command;

export class CommandSequence : public Command<bool>
{
public:
	template <std::input_iterator<std::unique_ptr<Command<bool>>> iter_type>
	CommandSequence(const iter_type& first, const iter_type& last, 
		const std::chrono::duration<float>& limit)
		: _commands(first, last), _timeLimit(limit) {};
	//Command
	void update(TimeStep timestep) override;
protected:
	[[nodiscard]] bool poll() const override;
private:
	[[nodiscard]] bool is_complete() const;
	[[nodiscard]] bool is_expired() const;
	std::vector<std::unique_ptr<Command<bool>>>::iterator _current;
	std::chrono::duration<float> _timeLimit, _elapsedTime{};
	std::vector<std::unique_ptr<Command<bool>>> _commands;
	void advance();
	void reset();
};

bool CommandSequence::is_complete() const
{
	return _current == _commands.end();
}

bool CommandSequence::is_expired() const
{
	return _elapsedTime > _timeLimit;
}

void CommandSequence::update(TimeStep timestep)
{
	_elapsedTime += timestep.scaled_time();
	(*_current)->update(timestep);
	Command<bool>::update(timestep);

	if (is_complete() || is_expired())
		reset();
	else if ((*_current)->get_value())
		advance();
}

bool CommandSequence::poll() const
{
	return is_complete();
}

void CommandSequence::advance()
{
	++_current;
	_elapsedTime = std::chrono::seconds::zero();
}

void CommandSequence::reset()
{
	_current = _commands.begin();
	_elapsedTime = std::chrono::seconds::zero();
}
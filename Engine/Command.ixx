module;
#include <algorithm>
#include <concepts>
#include <functional>
#include <memory>
#include <SFML/System.hpp>
#include <vector>
#include <chrono>
export module Command;

import TimeStep;

export template <typename value_type>
class Command
{
public:
	virtual void update(TimeStep timestep) = 0;
	[[nodiscard]] virtual value_type poll() const = 0;
};

export template <typename value_type>
class CommandMatch : public Command<bool>
{
public:
	CommandMatch(std::shared_ptr<Command<value_type>>, const value_type& target,
		const std::function<bool(value_type, value_type)> = std::equal_to<value_type>);
	[[nodiscard]] bool poll() const override;
private:
	std::unique_ptr<Command<value_type>> _delegate;
	value_type _target;
	std::function<bool(value_type, value_type)> _predicate;
};

template<typename value_type>
bool CommandMatch<value_type>::poll() const
{
	return _predicate(_delegate->read() == _target);
}

export class CompositeCommand : public Command<bool>
{
public:
	template <typename iter_type>
	CompositeCommand(const iter_type& first, const iter_type& last) :
		_commands(first, last) {};
protected:
	std::vector<std::shared_ptr<Command<bool>>> _commands;
};

export class CommandCombination : public CompositeCommand
{
public:
	template <typename iter_type>
	CommandCombination(const iter_type& first, const iter_type& last)
		: CompositeCommand(first, last) {};
	void update(TimeStep timestep) override;
	[[nodiscard]] bool poll() const override;
};

void CommandCombination::update(TimeStep timestep)
{
	for (auto& command : _commands)
		command->update(timestep);
}

bool CommandCombination::poll() const
{
	return std::all_of(_commands.begin(), _commands.end(), 
		[](const auto& command) { return command->poll(); }
	);
}

export class CommandSequence : public CompositeCommand
{
public:
	template <typename iter_type>
	CommandSequence(const iter_type& first, const iter_type& last, const std::chrono::duration<float> & limit)
		: CompositeCommand(first, last), _timeLimit(limit) {};
	void update(TimeStep timestep) override;
	[[nodiscard]] bool poll() const override;
private:
	int _index = 0;
	std::chrono::duration<float> _timeLimit, _elapsedTime{};
	[[nodiscard]] bool is_complete() const;
	[[nodiscard]] bool is_expired() const;
	[[nodiscard]] std::shared_ptr<Command<bool>> current() const;
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
	return _commands[_index];
}

void CommandSequence::update(TimeStep timestep)
{
	_elapsedTime += timestep.scaled_time();
	current()->update(timestep);
	if (is_complete() || is_expired())
		reset();
	else if (current()->poll())
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

//Game Engine Architecture, Third Edition, pg. 577
export class CommandTap : public Command<bool>
{
public:
	CommandTap() = default;
	//CommandTap(std::shared_ptr<Command<bool>> command, float frequency) : _delegate(command), _frequency(frequency) {};
	CommandTap(std::shared_ptr<Command<bool>> command, const std::chrono::seconds & period) 
		: _delegate(command), _period(period) {};
	[[nodiscard]] std::chrono::duration<float> elapsed() const{ return _elapsed; };
	//Command
	void update(TimeStep timestep) override;
	[[nodiscard]] bool poll() const override;
private:
	std::shared_ptr<Command<bool>> _delegate;
	std::chrono::duration<float> _elapsed, _period;
};

void CommandTap::update(TimeStep timestep)
{
	_delegate->update(timestep);
	_elapsed = _delegate->poll() ? std::chrono::seconds::zero() : _elapsed + timestep.scaled_time();
}

bool CommandTap::poll() const
{
	return _elapsed <= _period;
}
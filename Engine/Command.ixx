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
	virtual value_type get_value() const = 0;
protected:
	[[nodiscard]] virtual value_type poll() const = 0;
};

export template<>
class Command<bool>
{
public: 
	[[nodiscard]] constexpr bool was_pressed() const { return _isDown && !_wasDown; };
	[[nodiscard]] constexpr bool is_down() const { return _isDown; };
	[[nodiscard]] constexpr bool was_released() const { return !_isDown && _wasDown; };
	//Command
	virtual void update(TimeStep timestep);
	virtual bool get_value() const { return _isDown; };
protected:
	[[nodiscard]] virtual bool poll() const = 0;
private:
	bool _wasDown = false, _isDown = false;
};

void Command<bool>::update(TimeStep timestep)
{
	_wasDown = _isDown;
	_isDown = poll();
}

export template <typename value_type>
class CommandMatch : public Command<bool>
{
public:
	using predicate_type = std::function<bool(value_type, value_type)>;
	CommandMatch(std::shared_ptr<Command<value_type>> command, 
		const value_type& target, 
		const predicate_type predicate = std::equal_to<value_type>) 
		: _delegate(command), _target(target), _predicate(predicate) {};
protected:
	//Command
	[[nodiscard]] bool poll() const override;
private:
	std::unique_ptr<Command<value_type>> _delegate;
	value_type _target;
	std::function<bool(value_type, value_type)> _predicate;
};

template<typename value_type>
bool CommandMatch<value_type>::poll() const
{
	return _predicate(_delegate->get_value(), _target);
}

export class CommandCombination : Command<bool>
{
public:
	template <typename iter_type>
	CommandCombination(const iter_type& first, const iter_type& last)
		: _commands(first, last) {};
	//Command
	void update(TimeStep timestep) override;
protected:
	//Command
	[[nodiscard]] bool poll() const override;
private:
	std::vector<std::shared_ptr<Command<bool>>> _commands;
};

void CommandCombination::update(TimeStep timestep)
{
	std::ranges::for_each(_commands, [timestep](auto& command) { command->update(timestep); });
	Command<bool>::update(timestep);
}

bool CommandCombination::poll() const
{
	return std::ranges::all_of(_commands, [](const auto& command) { return command->get_value(); });
}

export class CommandSequence : public Command<bool>
{
public:
	template <typename iter_type>
	CommandSequence(const iter_type& first, const iter_type& last, const std::chrono::duration<float> & limit)
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
	return _commands[std::min(_index, (int)_commands.size() -1 )];
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

//Game Engine Architecture, Third Edition, pg. 577
export class CommandTap : public Command<bool>
{
public:
	CommandTap(std::shared_ptr<Command<bool>> command, const std::chrono::seconds & period) 
		: _delegate(command), _period(period) {};
	//Command
	void update(TimeStep timestep) override;
protected:
	//Command
	[[nodiscard]] bool poll() const override;
private:
	std::shared_ptr<Command<bool>> _delegate;
	std::chrono::duration<float> _elapsed, _period;
};

void CommandTap::update(TimeStep timestep)
{
	_delegate->update(timestep);
	_elapsed = _delegate->get_value() ? std::chrono::seconds::zero() : _elapsed + timestep.scaled_time();
	Command<bool>::update(timestep);
}

bool CommandTap::poll() const
{
	return _elapsed <= _period;
}
module;
#include <memory>
#include <chrono>
export module CommandTap;

import Command;

//Game Engine Architecture, Third Edition, pg. 577
export class CommandTap : public Command<bool>
{
public:
	CommandTap(std::shared_ptr<Command<bool>> command, const std::chrono::seconds& period)
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
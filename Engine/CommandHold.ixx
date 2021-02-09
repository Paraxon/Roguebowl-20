module;
#include <chrono>
#include <memory>
export module CommandHold;

import Command;
import TimeStep;

export class CommandHold : public Command<bool>
{
public:
	CommandHold(std::shared_ptr<Command<bool>> command, std::chrono::duration<float> duration) 
		: _command(command), _duration(duration) {};
	void update(TimeStep timestep) override;
protected:
	[[nodiscard]] bool poll() const override;
private:
	std::chrono::duration<float> _elapsed, _duration;
	std::shared_ptr<Command<bool>> _command;
};

void CommandHold::update(TimeStep timestep)
{
	_command->update(timestep);
	_elapsed = _command->get_value() ? _elapsed + timestep.scaled_time() : std::chrono::duration<float>::zero();
	Command::update(timestep);
}

bool CommandHold::poll() const
{
	return _elapsed >= _duration;
}
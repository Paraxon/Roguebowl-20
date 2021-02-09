module;
#include <algorithm>
#include <memory>
#include <vector>
export module CommandCombination;

import Command;

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
module;
#include <functional>
#include <memory>
export module CommandMatch;

import Command;

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
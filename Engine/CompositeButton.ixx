module;
#include <memory>
#include <vector>
#include <concepts>
export module CompositeButton;

import Button;
import Command;
import Serialization;
import StaticFactory;
import TimeStep;

export class CompositeButton : public Button
{
public:
	[[nodiscard]] CompositeButton() = default;
	template <std::forward_iterator<std::shared_ptr<Button>> iter_type>
	[[nodiscard]] CompositeButton(const iter_type& first, const iter_type& last) : _buttons(first, last) {};
protected:
	std::vector<std::shared_ptr<Button>> _buttons;
};
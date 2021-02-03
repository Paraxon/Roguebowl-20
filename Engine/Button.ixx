module;
#include <memory>
#include <SFML/Window.hpp>
export module Button;

import Command;
import TimeStep;

export template<typename hardware_type>
class Button : public Command<bool>
{
public:
	[[nodiscard]] Button(const hardware_type & button) : _button(button) {};
	//Command
	[[nodiscard]] bool poll() const override;
protected:
	hardware_type _button;
};

export using MouseButton = Button<sf::Mouse::Button>;
export using KeyboardKey = Button<sf::Keyboard::Key>;

bool Button<sf::Mouse::Button>::poll() const
{
	return sf::Mouse::isButtonPressed(_button);
}

bool Button<sf::Keyboard::Key>::poll() const
{
	return sf::Keyboard::isKeyPressed(_button);
}
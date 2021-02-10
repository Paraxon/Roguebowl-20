module;
#include <SFML/Window.hpp>
export module Button;

import Command;

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

bool Button<sf::Mouse::Button>::poll() const
{
	return sf::Mouse::isButtonPressed(_button);
}

bool Button<sf::Keyboard::Key>::poll() const
{
	return sf::Keyboard::isKeyPressed(_button);
}
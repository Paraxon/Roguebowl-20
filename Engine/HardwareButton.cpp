import HardwareButton;

#include <SFML/Window.hpp>

template<>
bool HardwareButton<sf::Mouse::Button>::poll() const
{
	return sf::Mouse::isButtonPressed(_button);
}

template<>
bool HardwareButton<sf::Keyboard::Key>::poll() const
{
	return sf::Keyboard::isKeyPressed(_button);
}
#include <memory>
#include <SFML/System.hpp>

import ButtonTap;

void ButtonTap::update(TimeStep timestep)
{
	Button::update(timestep);
	_elapsed = _button->was_pressed() ? sf::seconds(0) : _elapsed + timestep.scaled_time();
}

std::unique_ptr<Button> ButtonTap::clone() const
{
	return std::make_unique<ButtonTap>();
}

bool ButtonTap::poll() const
{
	return 1 / _elapsed.asSeconds() >= _frequency;
}

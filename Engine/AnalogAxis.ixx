module;
#include <SFML/Window.hpp>
export module AnalogAxis;

import Axis;
import Command;

export class AnalogAxis : public Axis
{
public:
	AnalogAxis(const sf::Joystick::Axis axis, 
		unsigned int index = 0, std::size_t smoothing = 1)
		: _axis(axis), _index(index), Axis(smoothing) {};
	//Command
	[[nodiscard]] float poll() const override;
private:
	unsigned int _index;
	sf::Joystick::Axis _axis;
};

float AnalogAxis::poll() const
{
	return sf::Joystick::getAxisPosition(_index, _axis);
}
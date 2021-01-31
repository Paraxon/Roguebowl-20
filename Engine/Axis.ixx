module;
#include <SFML/Window.hpp>
#include <memory>
export module Axis;

import Command;
import Button;
import TimeStep;

export class Axis : public Command<float>
{
};

export class DigitalAxis : public Axis
{
public:
	[[nodiscard]] float poll() const override;
private:
	std::shared_ptr<Command<bool>> _positive, _negative;
};

float DigitalAxis::poll() const
{
	float value{ 0 };
	if (_positive && _positive->poll())
		value += 1.0f;
	if (_negative && _negative->poll())
		value -= 1.0f;
	return value;
}

export class AnalogAxis : public Axis
{
public:
	[[nodiscard]] float poll() const override;
private:
	unsigned int _index;
	sf::Joystick::Axis _axis;
};

float AnalogAxis::poll() const
{
	return sf::Joystick::getAxisPosition(_index, _axis);
}
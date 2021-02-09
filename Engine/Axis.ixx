module;
#include <SFML/Window.hpp>
#include <memory>
export module Axis;

import Command;
import Button;
import TimeStep;
import MovingAverage;

export class Axis : public Command<float>
{
public:
	Axis(std::size_t smoothing = 1) : Command<float>(smoothing) {};
protected:
	[[nodiscard]] virtual float poll() const = 0;
};

export class DigitalAxis : public Axis
{
public:
	DigitalAxis(std::shared_ptr<Command<bool>> positive, std::shared_ptr<Command<bool>> negative = nullptr, std::size_t smoothing = 1)
		: _positive(positive), _negative(negative), Axis(smoothing) {};
	void update(TimeStep timestep) override;
protected:
	[[nodiscard]] float poll() const override;
private:
	std::shared_ptr<Command<bool>> _positive, _negative;
};

void DigitalAxis::update(TimeStep timestep)
{
	_positive->update(timestep);
	_negative->update(timestep);
	Command<float>::update(timestep);
}

float DigitalAxis::poll() const
{
	float value{ 0 };
	if (_positive && _positive->get_value())
		value += 1.0f;
	if (_negative && _negative->get_value())
		value -= 1.0f;
	return value;
}

export class AnalogAxis : public Axis
{
public:
	AnalogAxis(const sf::Joystick::Axis axis, unsigned int index = 0, std::size_t smoothing = 1)
		: _axis(axis), _index(index), Axis(smoothing) {};
	[[nodiscard]] float poll() const override;
private:
	unsigned int _index;
	sf::Joystick::Axis _axis;
};

float AnalogAxis::poll() const
{
	return sf::Joystick::getAxisPosition(_index, _axis);
}
module;
#include <memory>
export module DigitalAxis;

import Axis;
import Command;

export class DigitalAxis : public Axis
{
public:
	DigitalAxis(std::unique_ptr<Command<bool>> positive, 
		std::unique_ptr<Command<bool>> negative = nullptr, std::size_t smoothing = 1)
		: _positive(std::move(positive)), _negative(std::move(negative)),
		Axis(smoothing) {};
	//Command
	void update(TimeStep timestep) override;
protected:
	[[nodiscard]] float poll() const override;
private:
	std::unique_ptr<Command<bool>> _positive, _negative;
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
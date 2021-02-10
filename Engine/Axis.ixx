module;
#include <cstddef>
export module Axis;

import Command;

export class Axis : public Command<float>
{
public:
	Axis(std::size_t smoothing = 1) : Command<float>(smoothing) {};
protected:
	[[nodiscard]] virtual float poll() const = 0;
};
export module Button;

import Command;
import Serialization;
import StaticFactory;
import std.core;
import TimeStep;

export class Button : 
	public Command<bool>,
	public StaticFactory<Button>
{
public:
	virtual ~Button() = default;
	[[nodiscard]] constexpr bool was_pressed() const { return _isDown && !_wasDown; };
	[[nodiscard]] constexpr bool is_down() const { return _isDown; };
	[[nodiscard]] constexpr bool was_released() const { return !_isDown && _wasDown; };
	//Command
	void update(TimeStep timestep) override;
	//Cloneable
	[[nodiscard]] virtual std::unique_ptr<Button> clone() const = 0;
protected:
	bool _wasDown = false, _isDown = false;
};
import Button;

import HardwareButton;
import std.core;
import std.memory;

std::map<std::string, std::shared_ptr<Button>> StaticFactory<Button>::_prototypes
{
	{"mouse_button", std::make_shared<MouseButton>()},
	{"keyboard_key", std::make_shared<KeyboardKey>()},
	//{"button_tap", std::make_shared<ButtonTap>()},
	//{"button_combination", std::make_shared<ButtonCombination>()},
	//{"button_sequence", std::make_shared<ButtonSequence>()}
};

void Button::update(TimeStep timestep)
{
	_wasDown = _isDown;
	_isDown = poll();
}
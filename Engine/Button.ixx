module;
#include <memory>
#include <SFML/Window.hpp>
export module Button;

import Command;
import TimeStep;

export template<typename hardware_type>
class Button : public Command<bool>
{
public:
	[[nodiscard]] Button(const hardware_type & button) : _button(button) {};
	[[nodiscard]] constexpr bool was_pressed() const { return _isDown && !_wasDown; };
	[[nodiscard]] constexpr bool is_down() const { return _isDown; };
	[[nodiscard]] constexpr bool was_released() const { return !_isDown && _wasDown; };
	//Command
	void update(TimeStep timestep) override;
	[[nodiscard]] bool poll() const override;
protected:
	bool _wasDown = false, _isDown = false;
	hardware_type _button;
};

template <typename hardware_type>
void Button<hardware_type>::update(TimeStep timestep)
{
	_wasDown = _isDown;
	_isDown = poll();
}

export using MouseButton = Button<sf::Mouse::Button>;
export using KeyboardKey = Button<sf::Keyboard::Key>;

template<>
bool Button<sf::Mouse::Button>::poll() const
{
	return sf::Mouse::isButtonPressed(_button);
}

template<>
bool Button<sf::Keyboard::Key>::poll() const
{
	return sf::Keyboard::isKeyPressed(_button);
}
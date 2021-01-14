module;
#include <SFML/Window.hpp>
#include <memory>
export module HardwareButton;

import Button;
import Command;
import Serialization;
import StaticFactory;
import TimeStep;

export template <typename hardware_type>
class HardwareButton : public Button
{
public:
	[[nodiscard]] HardwareButton() = default;
	[[nodiscard]] HardwareButton(const hardware_type button) : _button(button) {};
	//Cloneable
	[[nodiscard]] std::unique_ptr<Button> clone() const override;
protected:
	bool poll() const override;
private:
	hardware_type _button;
};

export using MouseButton = HardwareButton<sf::Mouse::Button>;
export using KeyboardKey = HardwareButton<sf::Keyboard::Key>;

template<typename hardware_type>
std::unique_ptr<Button> HardwareButton<hardware_type>::clone() const
{
	return std::make_unique<HardwareButton<hardware_type>>(_button);
}
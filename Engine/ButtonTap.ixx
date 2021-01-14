module;
#include <memory>
#include <SFML/System.hpp>
export module ButtonTap;

import TimeStep;
import Button;
import Command;
import StaticFactory;
import Serialization;

//Game Engine Architecture, Third Edition, pg. 577
export class ButtonTap : public Button
{
public:
	ButtonTap() = default;
	ButtonTap(std::unique_ptr<Button> button, float frequency)
		: _button(std::move(button)), _frequency(frequency) {};
	ButtonTap(std::unique_ptr<Button> button, sf::Time period)
		: _button(std::move(button)), _frequency(1 / period.asSeconds()) {};
	//Command
	void update(TimeStep timestep) override;
	//Cloneable
	std::unique_ptr<Button> clone() const override;
protected:
	//Command
	bool poll() const override;
private:
	float _frequency = 0.f;
	std::unique_ptr<Button> _button;
	sf::Time _elapsed;
};
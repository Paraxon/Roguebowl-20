#include <SFML/Window.hpp>
#include <iostream>
#include <chrono>
import HardwareButton;
import TimeStep;

int main()
{
	HardwareButton button(sf::Mouse::Button::Left);
	using namespace std::chrono_literals;
	TimeStep timestep{16ms};
	button.update(timestep);
	std::cout << button.is_down() << std::endl;
	return 0;
}
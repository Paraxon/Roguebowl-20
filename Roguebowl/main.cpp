#include <chrono>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
import Command;
import Axis;
import Button;
import MovingAverage;
import TimeStep;

int main()
{
	using namespace std::chrono_literals;
	AnalogAxis axis(sf::Joystick::R);

	//auto quit = Button(sf::Keyboard::Key::Space);
	//std::ofstream output{"output.csv"};
	/*TimeStep timestep{ 16ms };

	while (!quit.get_value())
	{
		sf::Joystick::update();
		++timestep;
		axis.update(timestep);
		quit.update(timestep);
		
		const auto str = fmt::format("{:10},{:10},{:10}\n", timestep.run_time(), axis.get_value(), axis.raw_value());
		std::cout << str;
		output << str;

		sf::sleep(sf::milliseconds(16));
	}*/

	return 0;
}
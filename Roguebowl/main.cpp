#include <SFML/Window.hpp>
#include <iostream>
#include <chrono>
#include <fmt/core.h>
#include <memory>
import Button;
import Command;
import TimeStep;

int main()
{
	using namespace std::chrono_literals;
	
	std::vector commands{
		std::make_shared<Button<sf::Keyboard::Key>>(sf::Keyboard::Key::Space),
		std::make_shared<Button<sf::Keyboard::Key>>(sf::Keyboard::Key::LControl)
	};

	auto command = CommandTap(commands.front(), 1s);
	TimeStep timestep{ 16ms };

	while (true)
	{
		command.update(timestep);
		std::cout << command.poll() << std::endl;
	}

	return 0;
}
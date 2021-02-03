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
		std::make_shared<Button<sf::Keyboard::Key>>(sf::Keyboard::Key::Q),
		std::make_shared<Button<sf::Keyboard::Key>>(sf::Keyboard::Key::E),
	};

	sf::Clock clock;
	auto sequence = std::make_shared<CommandSequence>(commands.begin(), commands.end(), std::chrono::duration<float>(0.5));
	auto tap = CommandTap{ sequence, 1s };

	while (true)
	{
		TimeStep timestep{ clock.restart() };
		tap.update(timestep);
		std::cout << tap.get_value() << std::endl;
	}

	return 0;
}
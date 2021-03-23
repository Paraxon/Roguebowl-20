module;
#include <SFML/Graphics.hpp>
export module Color;

export sf::Color hexToColor(const std::string_view& source)
{
	return sf::Color::Magenta;
}
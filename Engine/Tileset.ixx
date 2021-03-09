module;
#include <SFML/Graphics.hpp>
export module Tileset;

namespace tmx
{
	export class Tileset
	{
	private:
		unsigned int _firstGID;
		std::string _name;
		sf::Vector2u _tileSize;
		unsigned int _spacing;
		unsigned int _margin;
		unsigned int _count;
		unsigned int _columns;
		std::shared_ptr<sf::Texture> _texture;
	};
}
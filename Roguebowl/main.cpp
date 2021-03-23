#include <string>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>

import Map;
import AssetRegistry;
import Tileset;
import Locator;

int main()
{
	auto map = std::make_shared<tmx::Map>();
	map->load("dungeon.tmx");
}
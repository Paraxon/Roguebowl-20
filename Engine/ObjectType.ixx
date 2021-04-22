module;
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
export module ObjectType;

import Properties;
import Propertied;

namespace tmx
{
	export class ObjectType
	{
	public:
		void load(const pugi::xml_node& source);
	private:
		std::string _name;
		sf::Color _color;
		Properties _defaults;
	};
	void ObjectType::load(const pugi::xml_node& source)
	{
		const auto properties = source.select_nodes("//property[@default]");
		for (const auto property : properties)
		{
			_defaults.load(source, "default");
		}
	}
}
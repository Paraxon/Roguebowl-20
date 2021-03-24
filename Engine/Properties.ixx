module;
#include <map>
#include <string>
#include <variant>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
#include <functional>
export module Properties;

import Color;

namespace tmx
{
	export using Property = std::variant<std::string, int, float, bool, sf::Color, std::filesystem::path, unsigned int>;

	//https://docs.mapeditor.org/en/latest/reference/tmx-map-format/#properties
	export class Properties
	{
	public:
		void load(const pugi::xml_node& source);
	private:
		std::map<std::string, Property> _values;
	};

	void Properties::load(const pugi::xml_node& source)
	{
		static const std::map<std::string, std::function<Property(pugi::xml_attribute)>> factories
		{
			{ "string", [](const pugi::xml_attribute value) { return value.as_string(); }},
			{ "int",	[](const pugi::xml_attribute value) { return value.as_int(); }},
			{ "float",	[](const pugi::xml_attribute value) { return value.as_float(); }},
			{ "bool",	[](const pugi::xml_attribute value) { return value.as_bool(); }},
			{ "color",	[](const pugi::xml_attribute value) { return hexToColor(value.as_string()); }},
			{ "file",	[](const pugi::xml_attribute value) { return std::filesystem::path{value.as_string()}; }},
			{ "object", [](const pugi::xml_attribute value) { return value.as_uint(); }}
		};
		for (const auto & child : source.children("property"))
		{
			const auto name = child.attribute("name").as_string();
			const auto type = child.attribute("type").as_string();
			const auto value = child.attribute("value");
			_values[name] = factories.at(type)(value);
		}
	}
}
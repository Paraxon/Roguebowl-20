module;
#include <map>
#include <string>
#include <variant>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
#include <functional>
#include <algorithm>
#include <fmt/core.h>
export module Properties;

import Color;

namespace tmx
{
	export using Property = std::variant<std::string, int, float, bool, sf::Color, std::filesystem::path, unsigned int>;

	//https://docs.mapeditor.org/en/latest/reference/tmx-map-format/#properties
	export class Properties
	{
	public:
		void load(const pugi::xml_node& source, const std::string & xpath = "value");
	private:
		std::map<std::string, Property> _values;
	};

	void Properties::load(const pugi::xml_node& source, const std::string & xpath)
	{
		static const std::map<std::string, std::function<Property(const pugi::xml_attribute &)>> factories {
			{ "string", [](const pugi::xml_attribute & value) { return value.as_string(); }},
			{ "int",	[](const pugi::xml_attribute & value) { return value.as_int(); }},
			{ "float",	[](const pugi::xml_attribute & value) { return value.as_float(); }},
			{ "bool",	[](const pugi::xml_attribute & value) { return value.as_bool(); }},
			{ "color",	[](const pugi::xml_attribute & value) { return hexToColor(value.as_string()); }},
			{ "file",	[](const pugi::xml_attribute & value) { return std::filesystem::path{value.as_string()}; }},
			{ "object", [](const pugi::xml_attribute & value) { return value.as_uint(); }}};

		const auto & children = source.select_nodes(fmt::format("/property[{}]", xpath).c_str());
		std::for_each(children.begin(), children.end(), [&](const auto & match) {
			const auto source = match.node();
			const auto name = source.attribute("name").as_string();
			const auto type = source.attribute("type").as_string();
			const auto value = source.attribute(xpath.c_str());
			_values[name] = factories.at(type)(value);
		});
	}
}
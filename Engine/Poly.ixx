module;
#include <vector>
#include <SFML/System.hpp>
#include <pugixml.hpp>
#include <sstream>
export module Poly;

namespace tmx
{
	export class Poly
	{
	public:
		void load(const pugi::xml_node& source);
	private:
		std::vector<sf::Vector2i> _points;
	};
	void Poly::load(const pugi::xml_node& source)
	{
		std::istringstream stream{ source.attribute("points").as_string() };
		const std::istream_iterator<std::string> first{ stream }, last;
		std::transform(first, last, std::back_inserter(_points), [] (const auto & value) -> sf::Vector2i {
			const auto comma = value.find(',');
			return {
				std::stoi(value.substr(0, comma)),
				std::stoi(value.substr(comma))
			};
		});
	}
}
module;
#include <string>
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
#include <map>
export module Text;

import Color;

namespace tmx
{
	//https://docs.mapeditor.org/en/latest/reference/tmx-map-format/#text
	export class Text
	{
	public:
		enum class HorizontalAlignment { Left, Center, Right, Justify };
		enum class VerticalAlignment { Top, Center, Bottom };
		void load(const pugi::xml_node& source);
	private:
		std::string _fontFamily;
		unsigned int _pixelSize;
		bool _wrap;
		sf::Color _color;
		bool _bold;
		bool _italic;
		bool _underline;
		bool _strikeout;
		bool _kerning;
		HorizontalAlignment _horizontal;
		VerticalAlignment _vertical;
	};

	void Text::load(const pugi::xml_node& source)
	{		
		const static std::map<std::string, HorizontalAlignment> hAligns
		{
			{ "left", HorizontalAlignment::Left },
			{ "center", HorizontalAlignment::Center },
			{ "right", HorizontalAlignment::Right },
			{ "justify", HorizontalAlignment::Justify }
		};
		const static std::map<std::string, VerticalAlignment> vAligns
		{
			{"top", VerticalAlignment::Top},
			{"center", VerticalAlignment::Center},
			{"bottom", VerticalAlignment::Bottom}
		};

		_fontFamily = source.attribute("fontfamily").as_string();
		_pixelSize = source.attribute("pixelsize").as_uint();
		_wrap = source.attribute("wrap").as_bool();
		_color = hexToColor(source.attribute("color").as_string());
		_bold = source.attribute("bold").as_bool();
		_italic = source.attribute("italic").as_bool();
		_underline = source.attribute("underline").as_bool();
		_strikeout = source.attribute("strikeout").as_bool();
		_kerning = source.attribute("kerning").as_bool();
		_horizontal = hAligns.at(source.attribute("halign").as_string());
		_vertical = vAligns.at(source.attribute("valign").as_string());
	}
}
module;
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
#include <filesystem>
export module Tileset;

import Object;

namespace tmx
{
	//https://docs.mapeditor.org/en/latest/reference/tmx-map-format/#tileset
	export class Tileset
	{
	public:
		Tileset(const unsigned int firstGID) : _firstGID(firstGID) {};
		void load(const std::filesystem::path& source);
		void load(const pugi::xml_node& source);
	private:
		unsigned int _firstGID;
		std::string _name;
		sf::Vector2u _tileSize;
		unsigned int _spacing;
		unsigned int _margin;
		unsigned int _count;
		unsigned int _columns;
		Object::Alignment _alignment;
		std::shared_ptr<sf::Texture> _texture;
	};

	void Tileset::load(const std::filesystem::path& source)
	{
		pugi::xml_document doc;
		const auto result = doc.load_file(source.c_str());
		load(doc.child("tileset"));
	}

	void Tileset::load(const pugi::xml_node& source)
	{
		std::map<std::string, Object::Alignment> alignments
		{
			{"unspecified", Object::Alignment::Unspecified},
			{"topleft", Object::Alignment::TopLeft},
			{"top", Object::Alignment::Top},
			{"topright", Object::Alignment::TopRight},
			{"left", Object::Alignment::Left},
			{"center", Object::Alignment::Center},
			{"right", Object::Alignment::Right},
			{"bottomleft", Object::Alignment::BottomLeft},
			{"bottom", Object::Alignment::Bottom},
			{"bottomright", Object::Alignment::BottomRight }
		};

		_name = source.attribute("name").as_string();
		_tileSize.x = source.attribute("tilewidth").as_uint();
		_tileSize.y = source.attribute("tileheight").as_uint();
		_spacing = source.attribute("spacing").as_uint();
		_margin = source.attribute("margin").as_uint();
		_count = source.attribute("tilecount").as_uint();
		_columns = source.attribute("columns").as_uint();
		_alignment = alignments.at(source.attribute("objectalignment").as_string("unspecified"));
	}
}
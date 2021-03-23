#include <exception>
#include <filesystem>
#include <map>
#include <memory>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>

import Color;
import CompositeLayer;
import Map;
import Tileset;

namespace tmx 
{
	void Map::load(const std::filesystem::path& path)
	{
		pugi::xml_document doc;
		const auto result = doc.load_file(path.c_str());
		load(doc.child("map"));
	}
	void Map::load(const pugi::xml_node& source)
	{
		static const std::map<std::string, Orientation> orientations
		{
			{"orthogonal", Orientation::Orthogonal},
			{"isometric", Orientation::Isometric},
			{"staggered", Orientation::Staggered},
			{"hexagonal", Orientation::Hexagonal}
		};
		static const std::map<std::string, RenderOrder> renderOrders
		{
			{"right-down", RenderOrder::RightDown},
			{"right-up", RenderOrder::RightUp},
			{"left-down", RenderOrder::LeftDown},
			{"left-up", RenderOrder::LeftUp}
		};
		static const std::map<std::string, StaggerAxis> staggerAxes
		{
			{"x", StaggerAxis::X },
			{"y", StaggerAxis::Y }
		};
		static const std::map<std::string, StaggerIndex> staggerIndices
		{
			{"even", StaggerIndex::Even},
			{"odd", StaggerIndex::Odd}
		};

		_version = source.attribute("version").as_string();
		_tiledVersion = source.attribute("tiledversion").as_string();
		_orientation = orientations.at(source.attribute("orientation").as_string());
		_renderOrder = renderOrders.at(source.attribute("renderorder").as_string());
		_compressionLevel = source.attribute("compressionlevel").as_int();
		_size.x = source.attribute("width").as_uint();
		_size.y = source.attribute("height").as_uint();
		_tileSize.x = source.attribute("tilewidth").as_uint();
		_tileSize.y = source.attribute("tileheight").as_uint();
		_hexSideLength = source.attribute("hexsidelength").as_uint();
		_background = hexToColor(source.attribute("backgroundcolor").as_string());
		_nextLayer = source.attribute("nextlayerid").as_uint();
		_nextObject = source.attribute("nextobjectid").as_uint();
		_infinite = source.attribute("infinite").as_bool();

		//only on staggered and hexogonal
		if (_orientation == Orientation::Staggered || _orientation == Orientation::Hexagonal)
		{
			_staggerAxis = staggerAxes.at(source.attribute("staggeraxis").as_string("x"));
			_staggerIndex = staggerIndices.at(source.attribute("staggerindex").as_string());
		}

		if (_renderOrder != RenderOrder::RightDown)
			throw std::exception("TMX Render Order not supported.");
		if (_orientation != Orientation::Orthogonal)
			throw std::exception("TMX Orientation not supported.");

		const auto tilesets = source.children("tileset");
		std::transform(tilesets.begin(), tilesets.end(), std::back_inserter(_tilesets), [](const auto& node) {
			const auto firstGID = node.attribute("firstgid").as_uint();
			auto tileset = std::make_shared<Tileset>(firstGID);
			const auto path = node.attribute("source");
			path ? tileset->load(path.as_string()) : tileset->load(node);
			return tileset; });

		CompositeLayer::load(source);
	}
	std::shared_ptr<Map> Map::root() const
	{
		return std::dynamic_pointer_cast<Map>(std::const_pointer_cast<CompositeLayer>(shared_from_this()));
	}
	unsigned int Map::nextLayerID()
	{
		return ++_nextLayer;
	}
}
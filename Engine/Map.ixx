module;
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <pugixml.hpp>
#include <exception>
export module Map;

import Properties;
import Layer;
import LayerGroup;
import Serialization;

namespace tmx
{
	// https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#map
	export class Map : public LayerGroup
	{
	public:
		//Rule of 5
		~Map() = default;
		void load(const std::filesystem::path& path);
		void load(const pugi::xml_node& source);
		[[nodiscard]] std::unique_ptr<Layer> clone() const override;
		enum class Orientation { Orthogonal, Isometric, Staggered, Hexagonal };
		enum class RenderOrder { RightDown, RightUp, LeftDown, LeftUp };
		enum class StaggerAxis { X, Y };
		enum class StaggerIndex { Even, Odd };
	private:
		std::string _version;
		std::string _tiledVersion;
		Orientation _orientation;
		RenderOrder _renderOrder;
		int _compressionLevel;
		sf::Vector2u _size;
		sf::Vector2u _tileSize;
		unsigned int _hexSideLength;
		StaggerAxis _staggerAxis;
		StaggerIndex _staggerIndex;
		sf::Color _background;
		unsigned int _nextLayer;
		unsigned int _nextObject;
		bool _infinite;
		tmx::Properties _properties;
		std::vector<std::shared_ptr<Layer>> _children;
	};
	
	void Map::load(const std::filesystem::path& path)
	{
		pugi::xml_document doc;
		const auto result = doc.load_file(path.c_str());
		load(doc.child("map"));
	}
	
	void Map::load(const pugi::xml_node& source)
	{
		static std::map<std::string, Orientation> orientations
		{
			{"orthogonal", Orientation::Orthogonal},
			{"isometric", Orientation::Isometric},
			{"staggered", Orientation::Staggered},
			{"hexagonal", Orientation::Hexagonal}
		};
		static std::map<std::string, RenderOrder> renderOrders
		{
			{"right-down", RenderOrder::RightDown},
			{"right-up", RenderOrder::RightUp},
			{"left-down", RenderOrder::LeftDown},
			{"left-up", RenderOrder::LeftUp}
		};
		static std::map<std::string, StaggerAxis> staggerAxes
		{
			{"x", StaggerAxis::X },
			{"y", StaggerAxis::Y }
		};
		static std::map<std::string, StaggerIndex> staggerIndices
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

		LayerGroup::load(source);
	}

	std::unique_ptr<Layer> Map::clone() const
	{
		return std::make_unique<Map>();
	}
}
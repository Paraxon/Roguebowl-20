module;
#include <filesystem>
#include <memory>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
export module Map;

import CompositeLayer;

namespace tmx
{
	export class Tileset;

	// https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#map
	export class Map : public CompositeLayer
	{
	public:
		//Rule of 5
		~Map() = default;
		void load(const std::filesystem::path& path);
		void load(const pugi::xml_node& source) override;
		[[nodiscard]] std::shared_ptr<Map> root() const override;
		[[nodiscard]] unsigned int nextLayerID();
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
		std::vector<std::shared_ptr<Tileset>> _tilesets;
	};
}
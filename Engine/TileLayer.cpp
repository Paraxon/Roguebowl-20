#include <memory>
#include <SFML/Graphics.hpp>

import Layer;
import TileLayer;

namespace tmx
{
	std::unique_ptr<Layer> TileLayer::clone(unsigned int id, std::shared_ptr<CompositeLayer> parent) const
	{
		return std::make_unique<TileLayer>(id, parent);
	}

	void TileLayer::load(const pugi::xml_node& source)
	{
		Layer::load(source);
		_position.x = source.attribute("x").as_float();
		_position.y = source.attribute("y").as_float();
		_parallax.x = source.attribute("parallaxx").as_float();
		_parallax.y = source.attribute("parallaxy").as_float();
		_size.x = source.attribute("width").as_uint();
		_size.y = source.attribute("height").as_uint();
	}
}
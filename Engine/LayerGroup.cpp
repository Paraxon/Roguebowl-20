#include <memory>
#include <SFML/Graphics.hpp>

import LayerGroup;
import CompositeLayer;
import Layer;

namespace tmx
{
	std::unique_ptr<Layer> LayerGroup::clone(unsigned int id, std::shared_ptr<CompositeLayer> parent) const
	{
		return std::make_unique<LayerGroup>(id, parent);
	}
	void LayerGroup::load(const pugi::xml_node& source)
	{
		Layer::load(source);
		//CompositeLayer::load(source);
	}
}
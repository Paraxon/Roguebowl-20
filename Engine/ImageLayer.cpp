#include <memory>
#include <SFML/Graphics.hpp>

import ImageLayer;

namespace tmx
{
	std::unique_ptr<Layer> ImageLayer::clone(unsigned int id, std::shared_ptr<CompositeLayer> parent) const
	{
		return std::make_unique<ImageLayer>(id, parent);
	}

	void ImageLayer::load(const pugi::xml_node& source)
	{
		Layer::load(source);
		///load image...
	}
}
module;
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
export module ImageLayer;

import Layer;

namespace tmx
{
	export class ImageLayer : public Layer
	{
	public:
		void load(const pugi::xml_node& source) override;
	};

	void ImageLayer::load(const pugi::xml_node& source)
	{
		Layer::load(source);
		///load image...
	}
}
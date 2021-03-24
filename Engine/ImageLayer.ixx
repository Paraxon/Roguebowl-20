module;
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
export module ImageLayer;

export import Layer;

namespace tmx
{
	//https://docs.mapeditor.org/en/latest/reference/tmx-map-format/#imagelayer
	export class ImageLayer : public Layer
	{
	public:
		using Layer::Layer;
		void load(const pugi::xml_node& source) override;
		[[nodiscard]] std::unique_ptr<Layer> clone(unsigned int id, std::shared_ptr<CompositeLayer> parent) const override;
	};
}
module;
#include <memory>
#include <pugixml.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
export module LayerGroup;

export import CompositeLayer;
export import Layer;

namespace tmx
{
	export class LayerGroup : public Layer, public CompositeLayer
	{
	public:
		using Layer::Layer;
		[[nodiscard]] std::unique_ptr<Layer> clone(unsigned int id, std::shared_ptr<CompositeLayer> parent) const override;
		void load(const pugi::xml_node& source) override;
		[[nodiscard]] std::shared_ptr<Map> root() const override;
	private:
		std::vector<std::shared_ptr<Layer>> _children;
	};
}
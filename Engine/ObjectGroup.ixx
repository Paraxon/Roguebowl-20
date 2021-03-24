module;
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
#include <vector>
#include <memory>
export module ObjectGroup;

export import Layer;

namespace tmx
{
	export class Object;

	//https://docs.mapeditor.org/en/latest/reference/tmx-map-format/#objectgroup
	export class ObjectGroup : public Layer
	{
	public:
		using Layer::Layer;
		enum class DrawOrder { TopDown, Index };
		void load(const pugi::xml_node& source) override;
		[[nodiscard]] std::unique_ptr<Layer> clone(unsigned int id, std::shared_ptr<CompositeLayer> parent) const override;
	private:
		sf::Color _color;
		DrawOrder _drawOrder;
		std::vector<std::shared_ptr<Object>> _children;
	};
}
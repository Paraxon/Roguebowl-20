#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

import ObjectGroup;

namespace tmx
{
	std::unique_ptr<Layer> ObjectGroup::clone(unsigned int id, std::shared_ptr<CompositeLayer> parent) const
	{
		return std::make_unique<ObjectGroup>(id, parent);
	}

	void ObjectGroup::load(const pugi::xml_node& source)
	{
		static std::map<std::string, DrawOrder> drawOrders
		{
			{"topdown", DrawOrder::TopDown },
			{"index", DrawOrder::Index }
		};

		Layer::load(source);
		_color = hexToColor(source.attribute("color").as_string());
		_drawOrder = drawOrders.at(source.attribute("draworder").as_string("topdown"));

		/*for (const auto child : source.select_nodes("object|ellipse|point|polygon|polyline|text"))
		{

		}*/
	}
}
module;
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
#include <map>
export module ObjectLayer;

import Layer;
import Serialization;
import Object;

namespace tmx
{
	export class ObjectGroup : public Layer
	{
	public:
		enum class DrawOrder { TopDown, Index };
		void load(const pugi::xml_node& source) override;
	private:
		sf::Color _color;
		DrawOrder _drawOrder;
		std::vector<std::shared_ptr<Object>> _children;
	};

	void ObjectGroup::load(const pugi::xml_node& source)
	{
		static std::map<std::string, DrawOrder> drawOrders
		{
			{"topdown", DrawOrder::TopDown },
			{"index", DrawOrder::Index }
		};

		Layer::load(source);
		_color = hexToColor(source.attribute("color").as_string());
		_drawOrder = drawOrders.at(source.attribute("draworder").as_string());

		/*for (const auto child : source.select_nodes("object|ellipse|point|polygon|polyline|text"))
		{

		}*/
	}
}
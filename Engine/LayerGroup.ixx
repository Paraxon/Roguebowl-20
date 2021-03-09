module;
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
export module LayerGroup;

import Layer;

namespace tmx
{
	export class LayerGroup : public Layer
	{
	public:
		void load(const pugi::xml_node& source) override;
	private:
		std::vector<std::shared_ptr<Layer>> _children;
	};

	void LayerGroup::load(const pugi::xml_node& source)
	{
		Layer::load(source);
		/*for (const auto & child : source.select_nodes("layer|objectgroup|imagelayer|group"))
		{
			auto layer = StaticFactory<Layer>::create("");
		}*/
	}
}
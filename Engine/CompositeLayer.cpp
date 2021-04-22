#include <algorithm>
#include <memory>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>

import CompositeLayer;
import Layer;
import Map;

namespace tmx
{
	void CompositeLayer::load(const pugi::xml_node& source)
	{
		const auto nodes = source.select_nodes("layer|objectgroup|imagelayer|group");
		const auto parent = shared_from_this();
		const auto map = root();
		for (const auto match : nodes)
		{
			const auto& source = match.node();
			/*auto child = Layer::create(source.name(), map->nextLayerID(), parent);
			child->load(source);
			_children.push_back(child);*/
		}
		/*std::transform(nodes.begin(), nodes.end(), std::back_inserter(_children), [parent, map](const auto& match) {
			const auto& source = match.node();
			auto child = Layer::create(source.name(), map->nextLayerID(), parent);
			child->load(source);
			return child; });*/
	}
}
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
		const auto children = source.select_nodes("layer|objectgroup|imagelayer|group");
		/*std::transform(children.begin(), children.end(), std::back_inserter(_children), [parent = shared_from_this(), map = root()](const auto& match) {
			const auto& source = match.node();
			auto child = Layer::create(source.name(), map->nextLayerID(), parent);
			child->load(source);
			return child; });*/

		auto map = root();
		auto parent = shared_from_this();

		//for (const auto& match : children)
		//{
		//	const auto& node = match.node();
		//	auto child = Layer::create(node.name(), 0, nullptr);
		//	child->load(node);
		//	//_children.push_back(child);
		//}
	}
}
#include <map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

import Layer;
import TileLayer;
import ObjectGroup;
import ImageLayer;
//import LayerGroup;
import CompositeLayer;

//std::map<std::string, std::shared_ptr<tmx::Layer>> StaticFactory<tmx::Layer>::_prototypes
//{
//	{"layer", std::make_shared<tmx::TileLayer>(0, nullptr)},
//	{"objectgroup", std::make_shared<tmx::ObjectGroup>(0, nullptr)},
//	{"imagelayer", std::make_shared<tmx::ImageLayer>(0, nullptr)},
//	{"group", std::make_shared<tmx::LayerGroup>(0, nullptr)}
//};

namespace tmx
{
	void Layer::load(const pugi::xml_node& source)
	{
		_id = source.attribute("id").as_uint();
		_name = source.attribute("name").as_string();
		_opacity = source.attribute("opacity").as_float();
		_visible = source.attribute("visible").as_bool();
		_tint = hexToColor(source.attribute("tintcolor").as_string());
		_properties.load(source.child("properties"));
	}
	std::shared_ptr<CompositeLayer> Layer::parent() const
	{
		return _parent.lock();
	}
	std::shared_ptr<Map> Layer::root() const
	{
		return parent()->root();
	}
}
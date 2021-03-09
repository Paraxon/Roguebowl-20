module;
#include <cstddef>
#include <string>
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
export module Layer;

import Properties;
import StaticFactory;
import Serialization;

namespace tmx
{
	export class Layer : public StaticFactory<Layer>
	{
	public:
		virtual ~Layer() = default;
		[[nodiscard]] virtual std::unique_ptr<Layer> clone() const = 0;
		virtual void load(const pugi::xml_node& source);
	private:
		std::size_t _id;
		std::string _name;
		sf::Vector2f _position;
		sf::Vector2f _offset;
		sf::Vector2f _parallax;
		sf::Vector2u _size;
		float _opacity;
		bool _visible;
		sf::Color _tint;
		Properties _properties;
	};

	void Layer::load(const pugi::xml_node& source)
	{
		_id = source.attribute("id").as_uint();
		_name = source.attribute("name").as_string();
		_position.x = source.attribute("x").as_float();
		_position.y = source.attribute("y").as_float();
		_offset.x = source.attribute("offsetx").as_float();
		_offset.y = source.attribute("offsety").as_float();
		_parallax.x = source.attribute("parallaxx").as_float();
		_parallax.y = source.attribute("parallaxy").as_float();
		_size.x = source.attribute("width").as_uint();
		_size.y = source.attribute("height").as_uint();
		_opacity = source.attribute("opacity").as_float();
		_visible = source.attribute("visible").as_bool();
		_tint = hexToColor(source.attribute("tintcolor").as_string());

		_properties.load(source.child("properties"));
	}
}

//std::map<std::string, std::shared_ptr<tmx::Layer>> StaticFactory<tmx::Layer>::_prototypes
//{
//	{"", std::make_shared<tmx::Layer>()}
//};
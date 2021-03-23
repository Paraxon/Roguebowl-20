module;
#include <memory>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
#include <string>
export module Layer;

export import Properties;
export import StaticFactory;

namespace tmx
{
	export class CompositeLayer;
	export class Map;

	export class Layer : public StaticFactory<Layer>
	{
	public:
		Layer(unsigned int id, std::shared_ptr<CompositeLayer> parent) : _id(id), _parent(parent) {};
		virtual ~Layer() = default;
		[[nodiscard]] virtual std::unique_ptr<Layer> clone(unsigned int id, std::shared_ptr<CompositeLayer> parent) const = 0;
		virtual void load(const pugi::xml_node& source);
		[[nodiscard]] virtual std::shared_ptr<Map> root() const;
		[[nodiscard]] std::shared_ptr<CompositeLayer> parent() const;
	private:
		unsigned int _id;
		std::string _name;
		float _opacity;
		bool _visible;
		sf::Color _tint;
		sf::Vector2f _offset;
		Properties _properties;
		std::weak_ptr<CompositeLayer> _parent;
	};
}
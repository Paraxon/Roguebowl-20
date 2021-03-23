module;
#include <memory>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
export module CompositeLayer;

namespace tmx {
	
	export class Map;
	export class Layer;

	export class CompositeLayer : public std::enable_shared_from_this<CompositeLayer>
	{
	public:
		virtual ~CompositeLayer() = default;
		virtual void load(const pugi::xml_node& source);
		[[nodiscard]] virtual std::shared_ptr<Map> root() const = 0;
	private:
		std::vector<std::shared_ptr<Layer>> _children;
	};
}
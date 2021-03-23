module;
#include <memory>
#include <pugixml.hpp>
#include <SFML/Graphics.hpp>
export module TileLayer;

export import Layer;

namespace tmx
{
	export class TileLayer : public Layer
	{
	public:
		using Layer::Layer;
		[[nodiscard]] std::unique_ptr<Layer> clone(unsigned int id, std::shared_ptr<CompositeLayer> parent) const override;
		void load(const pugi::xml_node& source) override;
	private:
		sf::Vector2f _position;
		sf::Vector2f _parallax;
		sf::Vector2u _size;
	};
}
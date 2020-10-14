module;
#include <memory>
#include <SFML/Graphics.hpp>
export module Component;

import Composition;
import StaticFactory;
import Serialization;
import Updatable;

class Entity;
//class Scene;

export class Component :
	public sf::Drawable,
	public StaticFactory<Component>,
	public std::enable_shared_from_this<Component>,
	public Updatable
{
public:
	Component(std::shared_ptr<Entity> entity) : _entity(entity) {};
	[[nodiscard]] std::shared_ptr<Entity> entity();
	[[nodiscard]] std::shared_ptr<const Entity> entity() const { return _entity.lock(); };
	//updatable
	[[nodiscard]] std::shared_ptr<const Scene> scene() const override;
	//cloneable
	[[nodiscard]] virtual std::unique_ptr<Component> clone(const std::shared_ptr<Entity> & entity) = 0;
private:
	std::weak_ptr<Entity> _entity;
};
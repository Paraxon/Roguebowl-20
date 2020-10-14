module;
#include <SFML/Graphics.hpp>
export module System;

import StaticFactory;
import Updatable;
import Serialization;
import Composition;

export class System :
	public sf::Drawable,
	public StaticFactory<System>,
	public Updatable
{
public:
	System(std::shared_ptr<Scene> scene) : _scene(scene) {};
	//Updatable
	[[nodiscard]] std::shared_ptr<const Scene> scene() const override { return _scene.lock(); };
	//Cloneable
	[[nodiscard]] virtual std::unique_ptr<System> clone(const std::shared_ptr<Scene> & scene) const = 0;
private:
	std::weak_ptr<Scene> _scene;
};
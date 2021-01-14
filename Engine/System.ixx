module;
#include <SFML/Graphics.hpp>
export module System;

import StaticFactory;
import Updatable;
import Serialization;
import Composition;
import TimeStep;

export class System :
	public sf::Drawable,
	public StaticFactory<System>,
	public Updatable
{
public:
	//Rule of 5
	System(const System&) = delete;
	System(System&&) = delete;
	System& operator=(const System&) = delete;
	System& operator=(System&&) = delete;
	virtual ~System() = default;
	//Updatable
	[[nodiscard]] std::shared_ptr<const Scene> scene() const override { return _scene.lock(); };
	//Cloneable
	[[nodiscard]] virtual std::unique_ptr<System> clone(const std::shared_ptr<Scene> & scene) const = 0;
protected:
	System(std::shared_ptr<Scene> scene) : _scene(scene) {};
private:
	std::weak_ptr<Scene> _scene;
};
import Component;
import Entity;
import Scene;
#include <memory>
#include <SFML/Graphics.hpp>

std::shared_ptr<Entity> Component::entity()
{
	return const_pointer_cast<Entity>(
		static_cast<const Component&>(*this).entity());
}

std::shared_ptr<const Scene> Component::scene() const
{
	return entity()->scene();
}
import Entity;
import Component;
import Composition;
#include <SFML/Graphics.hpp>

Composition<Entity, Component>& Entity::components()
{
	return const_cast<Composition<Entity, Component> &>(
		static_cast<const Entity&>(*this).components());
}

void Entity::debug_draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (const auto & component : components())
		component->debug_draw(target, states);
}

void Entity::report_crash() const
{
	for (const auto& component : components())
		component->report_crash();
}

void Entity::start()
{
	for (const auto & component : components())
		component->start();
}

void Entity::update(TimeStep timestep)
{
	timestep *= timescale();
	for (const auto & component : components())
		component->update(timestep);
}

constexpr bool Entity::operator==(const Entity& other)
{
	return id() == other.id();
}
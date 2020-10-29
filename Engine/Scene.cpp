import Scene;
import System;
import Entity;
#include <SFML/System.hpp>

void Scene::update(sf::Time delta_time)
{
	delta_time *= timescale();
	for (auto & system : systems())
		system->update(delta_time);
	for (auto & entity : _entities)
		entity->update(delta_time);
}

void Scene::start()
{
	for (auto & system : systems())
		system->start();
	for (auto & entity : _entities)
		entity->start();
}

void Scene::report_crash() const
{
	for (auto & system : systems())
		system->report_crash();
	for (auto & entity : _entities)
		entity->report_crash();
}

void Scene::debug_draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(_camera);
	for (const auto & system : systems())
		system->debug_draw(target, states);
	for (const auto & entity : _entities)
		entity->debug_draw(target, states);
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(_camera);
	for (const auto & system : systems())
		target.draw(*system, states);
	for (const auto & entity : _entities)
		target.draw(*entity, states);
}
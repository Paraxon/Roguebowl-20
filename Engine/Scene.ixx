module;
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <vector>
export module Scene;

import Updatable;
import Composition;
import System;
import StaticFactory;
import Serialization;
import Entity;
import Component;

export class Scene :
	public sf::Drawable,
	public std::enable_shared_from_this<Scene>,
	public Updatable
{
public:
	void set_view(const sf::View & value) { _camera = value; };
	//Updatable
	[[nodiscard]] const Composition<Scene, System> & systems() const override { return _systems; };
	[[nodiscard]] std::shared_ptr<const Scene> scene() const override { return shared_from_this(); };
	[[nodiscard]] std::shared_ptr<Entity> create_entity(const unsigned int id = 0) override;
	[[nodiscard]] std::shared_ptr<Entity> find_entity(const unsigned int id) const override;
	//Debugging
	void report_crash() const override;
	void debug_draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	//Simulation
	void start() override;
	void update(sf::Time delta_time) override;
	//Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	//Serializable
	void load(const std::filesystem::path& path);
private:
	Composition<Scene, System> _systems;
	sf::View _camera;
	std::vector<std::shared_ptr<Entity>> _entities;
};
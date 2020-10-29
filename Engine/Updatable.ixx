module;
#include <memory>
#include <SFML/Graphics.hpp>
export module Updatable;

import Composition;
import Crash;

export class Scene;
export class Entity;
export class System;

export using id_type = unsigned int;

//"Updatable" spelt with one 'e'
//https://english.stackexchange.com/questions/56431/updatable-vs-Updatable-which-is-correct#56433

export class Updatable
{
public:
	//Rule of 5
	Updatable(const Updatable&) = delete;
	Updatable(Updatable&&) = delete;
	Updatable& operator=(const Updatable&) = delete;
	Updatable& operator=(Updatable&&) = delete;
	virtual ~Updatable() = default;
	//Scene
	[[nodiscard]] std::shared_ptr<Scene> scene();
	[[nodiscard]] virtual std::shared_ptr<const Scene> scene() const = 0;
	//Systems
	[[nodiscard]] Composition<Scene, System>& systems();
	[[nodiscard]] virtual const Composition<Scene, System>& systems() const;;
	//Entities
	[[nodiscard]] virtual std::shared_ptr<Entity> create_entity(const id_type id = 0);
	[[nodiscard]] virtual std::shared_ptr<Entity> find_entity(const id_type id) const;
	[[nodiscard]] virtual std::shared_ptr<Entity> get_entity(const id_type id);
	//Timescale
	[[nodiscard]] constexpr float timescale() const { return _timescale; };
	constexpr void set_timescale(const float value) { _timescale = value; };
	//Simulation
	virtual void start() {};
	virtual void update(sf::Time delta_time) = 0;
	//Debugging
	virtual void debug_draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void report_crash() const {};
protected:
	Updatable() = default;
private:
	float _timescale;
};
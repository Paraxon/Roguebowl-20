module;
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>
export module Entity;

import Updatable;
import Component;
import Composition;
import StaticFactory;
import Serialization;

export class Entity :
	public sf::Drawable,
	public sf::Transformable,
	public std::enable_shared_from_this<Entity>,
	public Updatable
{
public:
	Entity(std::shared_ptr<Scene> scene, id_type id) : _scene(scene), _id(id) {};
	constexpr bool operator == (const Entity & other);
	static bool can_create(const std::string& type);
	std::shared_ptr<Entity> create_child();
	//Components
	[[nodiscard]] Composition<Entity, Component> & components();
	[[nodiscard]] constexpr const Composition<Entity, Component>& components() const { return _components; };
	//ID
	[[nodiscard]] constexpr id_type id() const { return _id; };
	//Name
	[[nodiscard]] constexpr const std::string & name() const { return _name; };
	void rename(const std::string & value) { _name = value; };
	//Scene
	[[nodiscard]] std::shared_ptr<const Scene> scene() const override { return _scene.lock(); };
	//Debugging
	void debug_draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void report_crash() const override;
	//Simulation
	void start();
	void update(sf::Time delta_time);
	//Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	//Serializable
	void load(const pugi::xml_node& source);
private:
	Composition<Entity, Component> _components;
	std::string _name;
	const id_type _id;
	std::weak_ptr<Scene> _scene;
	bool _visible = true;
};
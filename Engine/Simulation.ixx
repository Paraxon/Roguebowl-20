module;
#include <functional>
#include <SFML/Graphics.hpp>
#include <chrono>
export module Simulation;

import Component;
import Composition;
import Scene;
import TimeStep;
import Updatable;

export class Simulation :
	public Updatable,
	public sf::Drawable
{
public:
	Simulation();
	void run();
	//Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	//Updatable
	[[nodiscard]] std::shared_ptr<const Scene> scene() const override { return _scene; };
	//Simulation
	void start() override;
	void update(TimeStep delta_time) override;
	//Debugging
	[[nodiscard]] sf::Image screenshot() const;
	void debug_draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void report_crash() const override;
private:
	void handle_events();
	sf::RenderWindow _window;
	sf::Clock _clock;
	std::shared_ptr<Scene> _scene;
	bool _debug = false;
	TimeStep _timestep = sf::seconds(1.f / 60);
	std::chrono::duration<float> _budget;
	std::map<sf::Event::EventType, std::vector<std::function<void(const sf::Event)>>> _delegates;
};
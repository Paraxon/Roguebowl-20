module;
#include <functional>
#include <SFML/Graphics.hpp>
export module Game;

import Updatable;
import Composition;
import Scene;
import Component;

export class Game :
	public Updatable,
	public sf::Drawable
{
public:
	Game();
	void run();
	//Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	//Updatable
	[[nodiscard]] std::shared_ptr<const Scene> scene() const override { return _scene; };
	//Simulation
	void start() override;
	void update(sf::Time delta_time) override;
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
	sf::Time _timeStep = sf::seconds(1 / 60.0f), _budget;
	std::map<sf::Event::EventType, std::vector<std::function<void(const sf::Event)>>> _delegates;
};
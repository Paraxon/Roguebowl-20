#include <filesystem>
#include <SFML/Graphics.hpp>
#include <chrono>

import Locator;
import Logger;
import Scene;
import Simulation;
import Terminal;
import TimeStep;

Simulation::Simulation()
{
	//services
	//Locator<Logger>::get().load("logger.xml");
	auto channel = std::make_shared<Terminal>();
	Locator<Logger>::get().set_prototype(channel);
	//Locator<tmx::TypesCollection>::get().load("object_types.xml");
	//Locator<CompositionFactory<Entity, Component>>::get().load("entity_types.xml");
	//Locator<CompositionFactory<Scene, System>>::get().load("scene_types.xml");

	//window
	_window.create(sf::VideoMode(720, 720), "Roguebowl 20");

	//scene
	//_scene = std::make_shared<Scene>();
	//_scene->initalize();
	//_scene->set_view(sf::View(sf::FloatRect(0, 0, 768, 768)));
	//_scene->load("dungeon.tmx");

	//events
	_delegates[sf::Event::KeyPressed].push_back([&](const auto event) {
		switch (event.key.code)
		{
			case sf::Keyboard::Tilde:
				_debug = !_debug;
				break;
			case sf::Keyboard::Escape:
				_window.close();
				break;
		}
	});
	_delegates[sf::Event::Closed].push_back([&](const auto event) {
		_window.close();
	});
}

void Simulation::run()
{
	start();
	while (_window.isOpen())
	{
		//update
		handle_events();
		++_timestep;
		_budget += _clock.restart();
		update(_timestep);

		//draw
		_window.clear(sf::Color::Blue);
		draw(_window, sf::RenderStates::Default);
		if (_debug)
			debug_draw(_window, sf::RenderStates::Default);
		_window.display();
	}
}

void Simulation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (scene())
		target.draw(*scene(), states);
}

void Simulation::start()
{
	if (scene())
		Updatable::scene()->start();
}

void Simulation::update(TimeStep timestep)
{
	timestep *= timescale();
	while (_budget >= timestep.scaled_time())
	{
		if (scene())
			Updatable::scene()->update(timestep);
		_budget -= timestep.scaled_time();
	}
}

void Simulation::report_crash() const
{
	/*report.set_screenshot(screenshot());
	scene()->report_crash(report);*/
}

sf::Image Simulation::screenshot() const
{
	sf::RenderTexture texture;
	const auto size = _window.getSize();
	texture.create(size.x, size.y);
	texture.draw(*this, sf::RenderStates::Default);
	return texture.getTexture().copyToImage();
}

void Simulation::debug_draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	scene()->debug_draw(target, states);
}

void Simulation::handle_events()
{
	sf::Event event;
	while (_window.pollEvent(event))
		for (const auto& delegate : _delegates[event.type])
			delegate(event);
}
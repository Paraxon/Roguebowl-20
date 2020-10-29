#include <filesystem>
#include <SFML/Graphics.hpp>
#include <chrono>
import Game;
import Locator;
import Logger;
import Scene;
import Terminal;

Game::Game()
{
	//services
	//Locator<Logger>::get().load("logger.xml");
	auto channel = std::make_shared<Terminal>();
	Locator<Logger>::get().set_prototype(channel);
	//const auto timer = Locator<Logger>::get().time("debug", Verbosity::Info, "initilization complete");
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
	_delegates[sf::Event::KeyPressed].push_back([this](const auto event) {
		if (event.key.code == sf::Keyboard::Tilde)
			_debug = !_debug;
		});
	_delegates[sf::Event::KeyPressed].push_back([this](const auto event) {
		if (event.key.code == sf::Keyboard::Escape)
			_window.close();
		});
	_delegates[sf::Event::Closed].push_back([this](const auto event) {
		event; _window.close();
		});
}

void Game::run()
{
	start();
	while (_window.isOpen())
	{
		//update
		handle_events();
		update(_clock.restart());

		//draw
		_window.clear(sf::Color::Black);
		draw(_window, sf::RenderStates::Default);
		if (_debug)
			debug_draw(_window, sf::RenderStates::Default);
		_window.display();
	}
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*scene(), states);
}

void Game::start()
{
	Updatable::scene()->start();
}

void Game::update(sf::Time delta_time)
{
	delta_time *= timescale();
	_budget += delta_time;
	while (_budget >= _timeStep)
	{
		Updatable::scene()->update(_timeStep);
		_budget -= _timeStep;
	}
}

void Game::report_crash() const
{
	/*report.set_screenshot(screenshot());
	scene()->report_crash(report);*/
}

sf::Image Game::screenshot() const
{
	sf::RenderTexture texture;
	const auto size = _window.getSize();
	texture.create(size.x, size.y);
	texture.draw(*this, sf::RenderStates::Default);
	return texture.getTexture().copyToImage();
}

void Game::debug_draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	scene()->debug_draw(target, states);
}

void Game::handle_events()
{
	sf::Event event;
	while (_window.pollEvent(event))
		for (const auto& delegate : _delegates[event.type])
			delegate(event);
}
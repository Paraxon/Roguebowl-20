import ButtonSequence;

#include <SFML/System.hpp>

void ButtonSequence::update(TimeStep timestep)
{
	Button::update(timestep);
	_elapsedTime += timestep.scaled_time();
	if (_index >= _buttons.size() || _elapsedTime > _timeLimit)
		reset();
	else if (_buttons[_index]->was_pressed())
		advance();
}

std::unique_ptr<Button> ButtonSequence::clone() const
{
	return std::make_unique<ButtonSequence>();
}

bool ButtonSequence::poll() const
{
	return _index >= _buttons.size();
}

void ButtonSequence::advance()
{
	++_index;
	_elapsedTime = sf::seconds(0);
}

void ButtonSequence::reset()
{
	_index = 0;
	_elapsedTime = sf::seconds(0);
}
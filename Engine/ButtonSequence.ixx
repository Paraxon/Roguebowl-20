module;
#include <SFML/System.hpp>
#include <concepts>
#include <memory>
export module ButtonSequence;

import Button;
import Command;
import Serialization;
import CompositeButton;
import StaticFactory;
import TimeStep;

export class ButtonSequence : public CompositeButton
{
public:
	ButtonSequence() = default;
	template <std::forward_iterator<std::shared_ptr<Button>> iter_type>
	ButtonSequence(const iter_type& first, const iter_type& last, sf::Time limit)
		: CompositeButton(first, last), _timeLimit(limit) {};
	//Command
	void update(TimeStep timestep) override;
	//Cloneable 
	std::unique_ptr<Button> clone() const override;
protected:
	//Command
	bool poll() const override;
private:
	void advance();
	void reset();
	int _index = 0;
	sf::Time _timeLimit, _elapsedTime;
};
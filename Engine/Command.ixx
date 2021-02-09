module;
#include <algorithm>
#include <concepts>
#include <functional>
#include <memory>
#include <SFML/System.hpp>
#include <vector>
#include <chrono>
export module Command;

import TimeStep;
import MovingAverage;

export template <typename value_type>
class Command
{
public:
	virtual void update(TimeStep timestep) = 0;
	[[nodiscard]] virtual value_type get_value() const = 0;
protected:
	[[nodiscard]] virtual value_type poll() const = 0;
};

export template<>
class Command<float>
{
public:
	Command(std::size_t smoothing = 1) : _filter(smoothing) {};
	[[nodiscard]] float raw_value() const;
	//Command
	virtual void update(TimeStep timestep);
	[[nodiscard]] virtual float get_value() const;
protected:
	[[nodiscard]] virtual float poll() const = 0;
private:
	float _value{ 0 };
	SimpleAverage<float> _filter;
};

void Command<float>::update(TimeStep timestep)
{
	_value = poll();
	_filter.add(_value);
}

float Command<float>::raw_value() const
{
	return _value;
}

float Command<float>::get_value() const
{
	return _filter.mean();
}

export template<>
class Command<bool>
{
public: 
	[[nodiscard]] constexpr bool was_pressed() const { return _isDown && !_wasDown; };
	[[nodiscard]] constexpr bool is_down() const { return _isDown; };
	[[nodiscard]] constexpr bool was_released() const { return !_isDown && _wasDown; };
	//Command
	virtual void update(TimeStep timestep);
	virtual bool get_value() const { return _isDown; };
protected:
	[[nodiscard]] virtual bool poll() const = 0;
private:
	bool _wasDown = false, _isDown = false;
};

void Command<bool>::update(TimeStep timestep)
{
	_wasDown = _isDown;
	_isDown = poll();
}
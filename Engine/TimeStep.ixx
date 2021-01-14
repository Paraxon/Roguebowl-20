module;
#include <SFML/System.hpp>
#include <chrono>
#include <concepts>
export module TimeStep;

export class TimeStep
{
public:
	TimeStep(const sf::Time & duration) : _duration(duration) {};
	TimeStep(const std::chrono::milliseconds & milliseconds) : _duration(sf::milliseconds(milliseconds.count())) {};
	TimeStep(const std::chrono::seconds & seconds) : _duration(sf::seconds(seconds.count())) {};
	//Time
	[[nodiscard]] sf::Time scaled_time() const;
	[[nodiscard]] sf::Time real_time() const;
	[[nodiscard]] sf::Time run_time() const;
	//Operators
	TimeStep& operator++(); //Pre-Increment
	template <std::floating_point scale_t> 
		TimeStep& operator *= (const scale_t& rhs);
	template <std::floating_point scale_t> 
		friend TimeStep operator * (TimeStep lhs, const scale_t& rhs);
private:
	float _scale = 1.f;
	sf::Int64 _frame = 0;
	const sf::Time _duration;
};

template<std::floating_point scale_t>
TimeStep& TimeStep::operator*=(const scale_t& rhs)
{
	_scale *= rhs;
	return *this;
}

template<std::floating_point scale_t>
TimeStep operator*(TimeStep lhs, const scale_t& rhs)
{
	lhs *= rhs;
	return lhs;
}

sf::Time TimeStep::scaled_time() const
{
	return _duration * _scale;
}

sf::Time TimeStep::real_time() const
{
	return _duration;
}

sf::Time TimeStep::run_time() const
{
	return _duration * _frame;
}

TimeStep& TimeStep::operator++()
{
	_frame++;
	return *this;
}

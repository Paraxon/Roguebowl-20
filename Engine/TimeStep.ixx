module;
#include <SFML/System.hpp>
#include <chrono>
#include <concepts>
export module TimeStep;

export class TimeStep
{
public:
	TimeStep(const sf::Time & duration) 
		: _duration(std::chrono::microseconds(duration.asMicroseconds())) {};
	template<typename duration_type>
	TimeStep(const duration_type& duration)
		: _duration(std::chrono::duration_cast<std::chrono::duration<float>>(duration)) {};
	//Time
	[[nodiscard]] std::chrono::duration<float> scaled_time() const;
	[[nodiscard]] std::chrono::duration<float> real_time() const;
	[[nodiscard]] std::chrono::duration<float> run_time() const;
	//Operators
	TimeStep& operator++(); //Pre-Increment
	template <std::floating_point scale_t> 
		TimeStep& operator *= (const scale_t& rhs);
	template <std::floating_point scale_t> 
		friend TimeStep operator * (TimeStep lhs, const scale_t& rhs);
private:
	float _scale = 1.f;
	unsigned int _frame = 0;
	const std::chrono::duration<float> _duration;
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

std::chrono::duration<float> TimeStep::scaled_time() const
{
	return _duration * _scale;
}

std::chrono::duration<float> TimeStep::real_time() const
{
	return _duration;
}

std::chrono::duration<float> TimeStep::run_time() const
{
	return _duration * _frame;
}

TimeStep& TimeStep::operator++()
{
	_frame++;
	return *this;
}

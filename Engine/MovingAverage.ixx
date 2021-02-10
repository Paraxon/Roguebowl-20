module;
#include <list>
#include <concepts>
export module MovingAverage;

export template <std::floating_point value_type>
class MovingAverage
{
public:
	virtual void add(const value_type & value) = 0;
	virtual value_type mean() const = 0;
};

//https://en.wikipedia.org/wiki/Moving_average#Simple_moving_average_(boxcar_filter)
export template <std::floating_point value_type>
class SimpleAverage : public MovingAverage<value_type>
{
public:
	SimpleAverage(const std::size_t size) : _size(size) {};
	void add(const value_type& value) override;
	value_type mean() const override;
private:
	value_type _avg{0};
	std::size_t _size, _count{};
};

template<std::floating_point value_type>
void SimpleAverage<value_type>::add(const value_type & value)
{
	const auto inverse_size = 1 / static_cast<float>(std::min(++_count, _size));
	_avg += inverse_size * (value - _avg);
}

template<std::floating_point value_type>
value_type SimpleAverage<value_type>::mean() const
{
	return _avg;
}
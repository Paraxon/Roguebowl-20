export module Event;

import std.core;

export class Event
{
public:
	Event(const std::string& type) : _type(type) {};
	[[nodiscard]] constexpr const std::string& type() const { return _type; };
	//Properties
	template <typename value_type>
	[[nodiscard]] constexpr std::optional<value_type> get(const std::string& name) const;
	template <typename value_type>
	constexpr void add(const std::string& name, const value_type& value);
private:
	std::string _type;
	std::map<std::string, std::any> _properties;
};


template<typename value_type>
constexpr std::optional<value_type> Event::get(const std::string& name) const
{
	const auto match = _properties.find(name);
	if (match == _properties.end() || typeid(value_type) != match->second.type() || !match->second.has_value())
		return std::nullopt;
	try {
		return std::any_cast<value_type>(_properties.at(name));
	}
	catch (const std::bad_any_cast&) {
		return std::nullopt;
	}
}

template<typename value_type>
constexpr void Event::add(const std::string& name, const value_type& value)
{
	_properties[name] = value;
}

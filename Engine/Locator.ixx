export module Locator;

export template <typename service_type>
class Locator
{
public:
	[[nodiscard]] static constexpr service_type & get() { return service; };
	static constexpr void set(const service_type & value) { service = value; };
private:
	static service_type service;
};

template <typename service_type>
service_type Locator<service_type>::service;
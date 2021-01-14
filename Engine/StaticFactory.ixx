module;
#include <string>
#include <memory>
#include <map>
export module StaticFactory;

import Serialization;

export template <typename product_type, typename identifier_type = std::string>
class StaticFactory
{
public:
	template <typename ... arg_types>
		requires Cloneable<product_type, arg_types ...>
	[[nodiscard]] static constexpr std::unique_ptr<product_type> create(const identifier_type & identifier, const arg_types & ... args);
	[[nodiscard]] static constexpr bool can_create(const identifier_type & identifier);
private:
	static std::map<identifier_type, std::shared_ptr<product_type>> _prototypes;
};

template<typename product_type, typename identifier_type>
template <typename ... arg_types>
	requires Cloneable<product_type, arg_types ...>
constexpr std::unique_ptr<product_type> StaticFactory<product_type, identifier_type>::create(const identifier_type & identifier, const arg_types & ... args)
{
	const auto prototype = _prototypes.find(identifier);
	return prototype != _prototypes.end() ? prototype->second->clone(args...) : nullptr;
}

template<typename product_type, typename identifier_type>
constexpr bool StaticFactory<product_type, identifier_type>::can_create(const identifier_type& type)
{
	return _prototypes.contains(type);
}
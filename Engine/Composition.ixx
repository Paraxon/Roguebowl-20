module;
#include <concepts>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
export module Composition;

import Logger;
import Locator;

/*Components cannot use "shared_from_this" to refer to themselves as their
derived type because they are stored as shared_ptrs to their base type. Instead,
they must either get a ptr to their base type from shared_from_this and cast to
the derived type or get themselves from the composition that owns them.*/

/*Abstract components will perfer to use the virtual functions of their base
class instead of overrides wherever the base function is not abstract.*/

export template <typename entity_type, typename component_type>
class Composition
{
public:
	Composition(std::shared_ptr<entity_type> entity = nullptr) : _entity(entity) {};
	
	//Creates and adds a new component, then returns the new component.
	template <std::derived_from<component_type> derived_type>
	std::shared_ptr<derived_type> create();
	
	//Tries to create the given component name by checking the static factory
	std::shared_ptr<component_type> create(const std::string & name);
	
	//Creates & adds a new component, then forwards its arguements to load the new component.
	template <std::derived_from<component_type> derived_type, typename ... arg_types>
		requires Serializable<derived_type, arg_types...>
	std::shared_ptr<derived_type> load(const arg_types & ... args);
	
	//Creates, adds & loads a new component given a matching component name
	template <typename ... arg_types> 
		requires Serializable<component_type, arg_types...>
	std::shared_ptr<component_type> load(const std::string & name, const arg_types& ... args);
	
	//Adds an exsisting component (usually created by cloning a prototype) to this composition.
	std::shared_ptr<component_type> add(const std::shared_ptr<component_type>& component);
	
	//Returns the first component that can be dynamicaly cast to the derived type.
	template <std::derived_from<component_type> derived_type> 
	[[nodiscard]] std::shared_ptr<derived_type> get() const;
	
	//Entity
	std::shared_ptr<entity_type> entity();
	std::shared_ptr<const entity_type> entity() const { return _entity.lock(); };
	void set_entity(const std::shared_ptr<entity_type> & value) { _entity = value; };
	
	//Cloneable
	Composition<entity_type, component_type> clone(const std::shared_ptr<entity_type> & entity) const;
	
	//Iterators
	constexpr auto begin() { return _components.begin(); };
	constexpr auto end() { return _components.end(); };
	constexpr auto begin() const { return _components.cbegin(); };
	constexpr auto end() const { return _components.cend(); };
private:
	std::weak_ptr<entity_type> _entity;
	std::vector<std::shared_ptr<component_type>> _components;
};

template <typename entity_type, typename component_type>
template<std::derived_from<component_type> derived_type>
std::shared_ptr<derived_type> Composition<entity_type, component_type>::create()
{
	auto component = std::make_shared<derived_type>(entity());
	return add(component);
}

template<typename entity_type, typename component_type>
template<std::derived_from<component_type> derived_type, typename ... arg_types>
	requires Serializable<derived_type, arg_types...>
std::shared_ptr<derived_type> Composition<entity_type, component_type>::load(const arg_types & ... args)
{
	auto component = create<derived_type>();
	component->load(args...);
	return component;
}

template<typename entity_type, typename component_type>
template<typename ...arg_types>
	requires Serializable<component_type, arg_types...>
std::shared_ptr<component_type> Composition<entity_type, component_type>::load(const std::string& name, const arg_types& ...args)
{
	auto component = create(name);
	if (component)
		component->load(args...); //dont try to load a nullptr
	return component;
}

template<typename entity_type, typename component_type>
std::shared_ptr<component_type> Composition<entity_type, component_type>::add(const std::shared_ptr<component_type>& component)
{
	if (!component)
		throw std::invalid_argument("attempted to add nullptr to composition");
	_components.push_back(component);
	return component;
}

template<typename entity_type, typename component_type>
std::shared_ptr<component_type> Composition<entity_type, component_type>::create(const std::string& name)
{
	//Check first that the component type can be created to avoid adding nullptrs to this composition
	return component_type::can_create(name) ? add(component_type::create(name, entity())) : nullptr;
}

template <typename entity_type, typename component_type>
template<std::derived_from<component_type> derived_type>
std::shared_ptr<derived_type> Composition<entity_type, component_type>::get() const
{
	std::shared_ptr<derived_type> derived;
	const auto match = std::find_if(begin(), end(), [&derived](const auto & component) {
		//Will evaluate to true when the cast to derived type is successful
		return derived = std::dynamic_pointer_cast<derived_type>(component);
	});
	/*if (match == end())
		Locator<Logger>::get().log("ECS", Verbosity::Warning, "Failed to find %s %s on subject %s.",
			typeid(component_type).name(),
			typeid(derived_type).name(),
			typeid(entity_type).name());*/
	return derived;
}

template<typename entity_type, typename component_type>
std::shared_ptr<entity_type> Composition<entity_type, component_type>::entity()
{
	return const_pointer_cast<entity_type>(
		static_cast<const Composition<entity_type, component_type> &>(*this).entity());
}

template<typename entity_type, typename component_type>
Composition<entity_type, component_type> Composition<entity_type, component_type>::clone(const std::shared_ptr<entity_type>& entity) const
{
	Composition<entity_type, component_type> clone{ entity };
	for (const auto & component : _components)
		clone.add(component->clone(entity));
	return clone;
}
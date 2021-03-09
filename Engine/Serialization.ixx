module;
#include <concepts>
#include <memory>
#include <filesystem>
#include <SFML/Graphics.hpp>
export module Serialization;

export template <typename clone_type, typename ... arg_types>
concept Cloneable = requires (const clone_type protoype, const arg_types ... args)
{
	{ protoype.clone(args...) } -> std::convertible_to<std::unique_ptr<clone_type>>;
};

export template <typename asset_type>
concept Loadable = requires (asset_type & asset, const std::filesystem::path & source)
{
	{ asset.loadFromFile(source.string()) } -> std::convertible_to<bool>;
};

export template <typename asset_type, typename ... source_types>
concept Serializable = requires (asset_type & asset, const source_types & ... sources)
{
	{ asset.load(sources...) } -> std::convertible_to<bool>;
};

export sf::Color hexToColor(const std::string_view& source)
{
	return sf::Color::Magenta;
}
module;
#include <filesystem>
#include <map>
#include <memory>
export module AssetRegistry;

import Serialization;

template <typename asset_type>
bool load(asset_type& asset, const std::filesystem::path path)
{
	asset.load(path);
	return true;
}

export template <typename asset_type>
class AssetRegistry
{
public:
	std::shared_ptr<asset_type> get(const std::filesystem::path & path);
private:
	std::map<std::filesystem::path, std::shared_ptr<asset_type>> assets;
};

template<typename asset_type>
std::shared_ptr<asset_type> AssetRegistry<asset_type>::get(const std::filesystem::path& path)
{
	const auto match = assets.find(path);
	if (match != assets.end())
		return match->second;

	auto asset = std::make_shared<asset_type>();
	if (load<asset_type>(*asset, path))
		return assets[path] = asset;
	else
		return nullptr;
}
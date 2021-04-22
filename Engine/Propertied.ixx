module;
#include <string>
export module Propertied;

namespace tmx
{
	export class Propertied
	{
	public:
		[[nodiscard]] virtual bool contains(const std::string& name) = 0;
	};
}
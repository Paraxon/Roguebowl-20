export module Object;

namespace tmx
{
	//https://docs.mapeditor.org/en/latest/reference/tmx-map-format/#object
	export class Object
	{
	public:
		enum class Alignment { Unspecified, TopLeft, Top, TopRight, Left, Center, Right, BottomLeft, Bottom, BottomRight };
	};
}
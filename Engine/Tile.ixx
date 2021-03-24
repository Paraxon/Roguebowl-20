export module Tile;

namespace tmx
{
	//https://docs.mapeditor.org/en/latest/reference/tmx-map-format/#tile
	export class Tile
	{
	private:
		unsigned int _id;
		float _probability;
	};
}
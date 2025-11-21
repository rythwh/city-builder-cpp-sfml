#pragma once

namespace world {
	enum class TileType
	{
		Ground,
		Water,
		Mountain
	};

	struct Tile 
	{
		TileType type;
		int buildingId; // -1 if no building
	};
} // namespace world
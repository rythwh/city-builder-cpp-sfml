#pragma once

#include "building_prefab.hpp"
#include "world/tile.hpp"

using namespace world;

namespace sim {
	struct Building {
		const BuildingPrefab& prefab;
		BuildingDensity density;
		BuildingLevel level;
		Tile& tile;
	};
}
#pragma once

#include "building_prefab.hpp"

namespace sim {
	struct Building {
		Building(
			const BuildingPrefab &prefab,
			BuildingDensity density,
			BuildingLevel level
		):
			prefab(prefab),
			density(density),
			level(level)
		{

		}

		const BuildingPrefab& prefab;
		BuildingDensity density;
		BuildingLevel level;
	};
}
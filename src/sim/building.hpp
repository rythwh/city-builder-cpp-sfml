#pragma once

#include "building_prefab.hpp"

namespace sim {
	class Building {
	public:
		Building(
			const BuildingPrefab& prefab,
			BuildingDensity density,
			BuildingLevel level
		):
			prefab(prefab),
			density(density),
			level(level)
		{
		}

		const long long id{(std::time(nullptr))};
		const BuildingPrefab& prefab;
		BuildingDensity density;
		BuildingLevel level;
	};
}
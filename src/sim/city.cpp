#include "city.hpp"

#include "world/tile.hpp"

namespace sim {
	City::City() {
	}

	void City::placeBuilding(const Building& building, Tile& tile) {
		if (tile.getBuilding() != nullptr) {
			removeBuilding(tile);
		}
		tile.setBuilding(building);
		// buildings.push_back(building);
	}

	void City::removeBuilding(Tile& tile) {
		Building* buildingPtr = tile.getBuilding();
		if (buildingPtr == nullptr) {
			return;
		}
		Building& building = *buildingPtr;

		// int buildingIndex = 0;
		// for (Building b : buildings) {
		// 	if (b.id == building.id) {
		// 		buildings.erase(buildings.begin() + buildingIndex);
		// 	}
		// 	++buildingIndex;
		// }
		tile.clearBuilding();
	}
}

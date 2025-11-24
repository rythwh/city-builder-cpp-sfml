#include "city.hpp"

#include "world/tile.hpp"

namespace sim {
	City::City() {

	}

	void City::placeBuilding(const Building& building, Tile& tile) {
		tile.setBuilding(building);
	}

	void City::removeBuilding(Tile& tile) {

	}
}

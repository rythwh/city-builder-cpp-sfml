#pragma once

#include "world/tile.hpp"

using namespace world;

namespace sim {
	class City {
	public:
		City();

		void placeBuilding(Building& building, Tile& tile);
		void removeBuilding(Tile& tile);
	private:
		int population{0};
		int funds{100000}; // Starting funds
	};
}
#include <vector>
#include <cmath>
#include <SFML/System/Vector2.hpp>

#include "map.hpp"
#include "tile.hpp"

using namespace sf;

namespace world {
	Map::Map(int width, int height) {
		size = Vector2i(width, height);
		tiles.resize(width * height);

		generateTerrain();
	}
	
	void Map::generateTerrain() {
		for (int y = 0; y < size.y; ++y) {
			for (int x = 0; x < size.x; ++x) {
				Tile& tile = getTile(x, y);
				// Simple height generation using sine waves
				float height = 10.f * (std::sin(x * 0.1f) + std::cos(y * 0.1f));
				// Determine tile type based on height
				if (height < 5.f) {
					tile.type = TileType::Water;
				} else if (height > 15.f) {
					tile.type = TileType::Mountain;
				} else {
					tile.type = TileType::Ground;
				}
				tile.buildingId = -1; // No building initially
			}
		}
	}
	
	Tile& Map::getTile(int x, int y) {
		return tiles[y * size.x + x];
	}
} // namespace world
#include "map.hpp"

#include <vector>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <ctime>

#include "tile.hpp"

using namespace sf;

namespace world {
	Map::Map(Vector2i size) : size(size) {
		tiles.resize(size.x * size.y);

		generateTerrain();
	}
	
	void Map::generateTerrain() {

		clock_t time = clock();

		const float wavelength = 30.f;

		for (int y = 0; y < size.y; ++y) {
			for (int x = 0; x < size.x; ++x) {
				Tile* tilePtr = getTile(x, y);
				if (tilePtr == nullptr) {
					continue;
				}
				Tile& tile = *tilePtr;

				tile.setPosition(x, y);

				// Simple height generation using sine waves
				// sin/cos return value between [-1, 1], summed to [-2, 2].
				// Add time for random position on wave, so terrain changes each call.
				// Normalize to [0, 1] by adding 2 for [0, 4] and dividing by 4 for [0, 1].
				float height = (std::sin((x + time) /  wavelength) + std::cos((y + time) /  wavelength) + 2) / 4.f;
				tile.setHeight(height);

				// Determine tile type based on height
				if (height < 0.2f) {
					tile.setType(TileType::Water);
				} else if (height > 0.8f) {
					tile.setType(TileType::Mountain);
				} else {
					tile.setType(TileType::Ground);
				}
			}
		}
	}

	/// @brief Return a modifiable Tile pointer at (x, y)
	/// @return nullptr if out of bounds, else pointer to Tile
	Tile* Map::getTile(int x, int y) {
		if (x < 0 || x >= size.x || y < 0 || y >= size.y) {
			return nullptr;
		}
		return &tiles[y * size.x + x];
	}

	/// @brief Return a read-only Tile pointer at (x, y)
	/// @return nullptr if out of bounds, else pointer to Tile
	const Tile* Map::getTile(int x, int y) const {
		if (x < 0 || x >= size.x || y < 0 || y >= size.y) {
			return nullptr;
		}
		return &tiles[y * size.x + x];
	}
} // namespace world
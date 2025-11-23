#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

#include "tile.hpp"

using namespace sf;

namespace world {
	class Map
	{
	public:
		Map(Vector2i size);

		void generateTerrain();

		/// @brief Return a modifiable Tile pointer at (x, y)
		/// @return nullptr if out of bounds, else pointer to Tile
		Tile* getTile(int x, int y);

		/// @brief Return a read-only Tile pointer at (x, y)
		/// @return nullptr if out of bounds, else pointer to Tile
		const Tile* getTile(int x, int y) const;
		
		const Vector2i getSize() const { 
			return size; 
		}
	private:
		Vector2i size;
		std::vector<Tile> tiles;
	};
} // namespace world
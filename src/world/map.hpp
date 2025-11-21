#pragma once

#include <vector>
#include "tile.hpp"
#include <SFML/System/Vector2.hpp>

using namespace sf;

namespace world {
	class Map
	{
	public:
		Map(int width, int height);

		void generateTerrain();
		Tile& getTile(int x, int y);
		
		const Vector2i getSize() const { 
			return size; 
		}
	private:
		Vector2i size;
		std::vector<Tile> tiles;
	};
} // namespace world
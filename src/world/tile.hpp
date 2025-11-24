#pragma once

#include <SFML/System/Vector2.hpp>

#include "sim/building.hpp"

using namespace sf;
using namespace sim;

namespace world {
	enum class TileType
	{
		Ground,
		Water,
		Mountain
	};

	class Tile
	{
	public:
		TileType getType() const { return type; }
		void setType(TileType newType) { type = newType; }

		float getHeight() const { return height; }
		void setHeight(float newHeight) { height = newHeight; }

		const Vector2i& getPosition() const { return position; }
		void setPosition(int x, int y) { position = {x, y}; }

		const Building* getBuilding() const { return building; }
		void setBuilding(Building& newBuilding) { building = &newBuilding; }
	private:
		TileType type;
		Vector2i position;
		float height;
		Building* building = nullptr;
	};
}
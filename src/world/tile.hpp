#pragma once

#include <SFML/System/Vector2.hpp>

using namespace sf;

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

		int getBuildingId() const { return buildingId; }
		void setBuildingId(int id) { buildingId = id; }

		const Vector2i& getPosition() const { return position; }
		void setPosition(int x, int y) { position = {x, y}; }
	private:
		TileType type;
		Vector2i position;
		float height;
		int buildingId{-1}; // -1 if no building
	};
}
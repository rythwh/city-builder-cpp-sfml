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

		void setBuilding(const Building& newBuilding) {
			building.emplace(newBuilding);
		}

		void clearBuilding() {
			building.reset();
		}

		bool hasBuilding() const {
			return building.has_value();
		}

		const Building* getBuilding() const {
			if (!building.has_value()) {
				return nullptr;
			}
			return &building.value();
		}

		Building* getBuilding() {
			if (!building.has_value()) {
				return nullptr;
			}
			return &building.value();
		}
	private:
		TileType type;
		Vector2i position;
		float height;

		std::optional<Building> building;
	};
}
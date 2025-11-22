#pragma once

#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace sim {
	enum class BuildingCategory
	{
		Empty,
		ResidentialLow,
		ResidentialMed,
		ResidentialHigh,
		CommercialLow,
		CommercialMed,
		CommercialHigh,
		IndustrialLow,
		IndustrialMed,
		IndustrialHigh,
		OfficeLow,
		OfficeMed,
		OfficeHigh,
		Park,
		Road
	};

	struct BuildingType {
		int id;
		std::string name;
		BuildingCategory category;

		Vector2i size; // Size in tiles (width, height)
		float cost;   // Cost to build
		int capacity;
	};
}
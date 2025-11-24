#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <string>

using namespace std;
using namespace sf;

namespace sim {

	enum class BuildingGroup {
		RICO,
		Service,
		Road
	};

	enum class BuildingCategory
	{
		Residential,
		Commercial,
		Industrial,
		Office,
		Park,
		Police,
		FireStation,
		Hospital,
		School,
		Road,

		Count // Keep last; Helper value for storing number of BuildingCategories
	};

	struct BuildingCategoryEntry {
		BuildingCategory buildingCategory;
		string_view name;
		Color color;
	};

	inline array<BuildingCategoryEntry, static_cast<int>(BuildingCategory::Count)> buildingCategories{
	{
		{ BuildingCategory::Residential,"Residential", Color( 46, 204, 113) },
		{ BuildingCategory::Commercial,"Commercial", Color( 52, 152, 219) },
		{ BuildingCategory::Industrial,"Industrial", Color(241, 196,  15) },
		{ BuildingCategory::Office,"Office", Color( 26, 188, 156) },
		{ BuildingCategory::Park,"Park", Color( 39, 174,  96) },
		{ BuildingCategory::Police,"Police", Color( 41, 128, 185) },
		{ BuildingCategory::FireStation,"Fire Station", Color(231,  76,  60) },
		{ BuildingCategory::Hospital,"Hospital", Color(163, 228, 215) },
		{ BuildingCategory::School,"School", Color(230, 126,  34) },
		{ BuildingCategory::Road,"Road", Color(149, 165, 166) }
	}};

	enum class BuildingDensity
	{
		Low,
		Medium,
		High,

		Count // Count helper
	};

	enum class BuildingLevel
	{
		Level1,
		Level2,
		Level3
	};

	struct BuildingPrefab {
		BuildingCategoryEntry buildingCategory;
		BuildingDensity density;
		int cost;
		int capacity;
	};

	inline array<BuildingPrefab, static_cast<int>(BuildingCategory::Count) * static_cast<int>(BuildingDensity::Count)> buildingPrefabs{{
		{ buildingCategories[static_cast<int>(BuildingCategory::Residential)], BuildingDensity::Low, 100, 4 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Residential)], BuildingDensity::Medium, 1000, 40 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Residential)], BuildingDensity::High, 10000, 400 },

		{ buildingCategories[static_cast<int>(BuildingCategory::Commercial)], BuildingDensity::Low, 70, 10 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Commercial)], BuildingDensity::Medium, 700, 50 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Commercial)], BuildingDensity::High, 7000, 150 },

		{ buildingCategories[static_cast<int>(BuildingCategory::Industrial)], BuildingDensity::Low, 30, 20 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Industrial)], BuildingDensity::Medium, 300, 50 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Industrial)], BuildingDensity::High, 3000, 200 },

		{ buildingCategories[static_cast<int>(BuildingCategory::Office)], BuildingDensity::Low, 30, 20 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Office)], BuildingDensity::Medium, 300, 50 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Office)], BuildingDensity::High, 3000, 200 },

		{ buildingCategories[static_cast<int>(BuildingCategory::Park)], BuildingDensity::Low, 10, 5 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Park)], BuildingDensity::Medium, 500, 30 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Park)], BuildingDensity::High, 2000, 100 },

		{ buildingCategories[static_cast<int>(BuildingCategory::Police)], BuildingDensity::Low, 500, 25 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Police)], BuildingDensity::High, 5000, 100 },

		{ buildingCategories[static_cast<int>(BuildingCategory::FireStation)], BuildingDensity::Low, 500, 25 },
		{ buildingCategories[static_cast<int>(BuildingCategory::FireStation)], BuildingDensity::High, 5000, 100 },

		{ buildingCategories[static_cast<int>(BuildingCategory::Hospital)], BuildingDensity::Low, 500, 25 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Hospital)], BuildingDensity::High, 5000, 100 },

		{ buildingCategories[static_cast<int>(BuildingCategory::School)], BuildingDensity::Low, 500, 300 },
		{ buildingCategories[static_cast<int>(BuildingCategory::School)], BuildingDensity::High, 5000, 2000 },

		{ buildingCategories[static_cast<int>(BuildingCategory::Road)], BuildingDensity::Low, 20, 2 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Road)], BuildingDensity::Medium, 80, 4 },
		{ buildingCategories[static_cast<int>(BuildingCategory::Road)], BuildingDensity::High, 800, 6 },
	}};
}
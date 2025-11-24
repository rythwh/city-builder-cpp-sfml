#pragma once

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

	constexpr array<BuildingCategoryEntry, static_cast<int>(BuildingCategory::Count)> buildingCategories{
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
		High
	};

	enum class BuildingLevel
	{
		Level1,
		Level2,
		Level3
	};

	struct BuildingPrefab {
		const int id;
		string name;
		BuildingCategory category;

		float cost;
		int capacity;
	};
}
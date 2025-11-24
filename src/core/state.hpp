#pragma once

#include "sim/building_prefab.hpp"

namespace core {
	class StateManager
	{
	public:
		enum class PlayState {
			Playing,
			Paused
		};

		enum class Mode {
			None,
			Build,
			Demolish
		};

		StateManager() : currentPlayState(PlayState::Playing), currentMode(Mode::None), selectedBuildingCategory() {}

		[[nodiscard]] PlayState getPlayState() const { return currentPlayState; }
		void setPlayState(const PlayState newPlayState) { currentPlayState = newPlayState; }

		[[nodiscard]] Mode getMode() const { return currentMode; }
		void setMode(const Mode newMode) { currentMode = newMode; }

		[[nodiscard]] sim::BuildingCategoryEntry getSelectedBuildingCategory() const { return selectedBuildingCategory; }
		void setSelectedBuildingCategory(const sim::BuildingCategoryEntry& buildingCategory) {
			selectedBuildingCategory = buildingCategory;
		}

	private:
		PlayState currentPlayState;
		Mode currentMode;

		sim::BuildingCategoryEntry selectedBuildingCategory;
	};
}

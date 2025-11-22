#pragma once

namespace core {
	class GameState
	{
	public:
		enum class PlayState {
			Playing,
			Paused
		};

		enum class Mode {
			None,
			Road,
			Build,
			Demolish
		};

		GameState() : currentPlayState(PlayState::Playing), currentMode(Mode::None) {}

		PlayState getPlayState() const { return currentPlayState; }
		void setPlayState(PlayState newPlayState) { currentPlayState = newPlayState; }

		Mode getMode() const { return currentMode; }
		void setMode(Mode newMode) { currentMode = newMode; }

	private:
		PlayState currentPlayState;
		Mode currentMode;
	};
}
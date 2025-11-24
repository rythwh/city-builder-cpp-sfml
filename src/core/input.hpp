#pragma once

#include <optional>
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "world/tile.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"
#include "core/time.hpp"
#include "ui/ui_manager.hpp"

using namespace sf;
using namespace world;
using namespace ui;

namespace core {
class InputManager {
public:

	InputManager(
		StateManager& stateManager,
		RenderWindow& window,
		Camera& camera,
		Map& map,
		TimeManager& timeManager,
		UiManager& uiManager
	);

	void update(const std::optional<Event> &inputEvent) const;

	[[nodiscard]] const Tile* getMouseHoverTile() const;
	Tile* getMouseHoverTile();
private:
	StateManager& stateManager;
	RenderWindow& window;
	Camera& camera;
	Map& map;
	TimeManager& timeManager;
	UiManager& uiManager;

	void processMovementInput() const;
	void processInput(const std::optional<Event> &inputEvent) const;
	void processMouseClick(const std::optional<Event> &inputEvent) const;
};
}
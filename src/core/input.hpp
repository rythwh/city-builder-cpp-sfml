#pragma once

#include <optional>
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "world/tile.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"
#include "core/time.hpp"

using namespace sf;
using namespace world;

namespace core {
class InputManager {
public:

	InputManager(
		StateManager& stateManager,
		RenderWindow& window,
		Camera& camera,
		Map& map,
		TimeManager& timeManager
	);

	void update(std::optional<Event> inputEvent);

	const Tile* getMouseHoverTile() const;
	Tile* getMouseHoverTile();

	void reset() {
		cachedMouseHoverTile = nullptr;
	}
private:
	Tile* cachedMouseHoverTile = nullptr;

	StateManager& stateManager;
	RenderWindow& window;
	Camera& camera;
	Map& map;
	TimeManager& timeManager;

	void processMovementInput();
	void processInput(std::optional<Event> inputEvent);
};
} // namespace core
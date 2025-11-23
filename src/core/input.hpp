#pragma once

#include <optional>
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "world/tile.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"

using namespace sf;
using namespace world;

namespace core {
class InputManager {
public:
	void processInput(
		std::optional<Event> inputEvent,
		core::GameState& state,
		RenderWindow& window,
		Camera& camera,
		Map& map
	);

	const Tile* getMouseHoverTile(
		const RenderWindow& window,
		const Camera& camera,
		const Map& map
	) const;

	Tile* getMouseHoverTile(
		const RenderWindow& window,
		const Camera& camera,
		Map& map
	);

	void reset() {
		cachedMouseHoverTile = nullptr;
	}
private:
	Tile* cachedMouseHoverTile = nullptr;
};
} // namespace core
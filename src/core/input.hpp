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
	void processInput(
		std::optional<Event> inputEvent,
		core::GameState& state,
		RenderWindow& window,
		Camera& camera,
		Map& map
	);

	const Tile* mouseHoverTile(
		const RenderWindow& window,
		const Camera& camera,
		const Map& map
	);

	Tile* mouseHoverTile(
		const RenderWindow& window,
		const Camera& camera,
		Map& map
	);
}
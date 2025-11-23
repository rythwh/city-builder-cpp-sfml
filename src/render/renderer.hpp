#pragma once

#include <SFML/Graphics.hpp>
#include "world/map.hpp"
#include "world/camera.hpp"
#include "core/input.hpp"

using namespace world;
using namespace sf;
using namespace core;

namespace render {
	class Renderer {
	public:
		Renderer(
			RenderWindow& window,
			const Map& map,
			const Camera& camera,
			const InputManager& inputManager
		);
		void renderFrame();
	private:
		RenderWindow& window;
		const Map& map;
		const Camera& camera;
		const InputManager& inputManager;

		void drawMap();
		void visualiseHeightmap(RectangleShape& tileShape, const Tile& tile);
		void drawBuildings();
		void drawMouseHoverTile();
	};
} // namespace render
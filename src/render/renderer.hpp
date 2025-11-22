#pragma once

#include <SFML/Graphics.hpp>
#include "world/map.hpp"
#include "world/camera.hpp"

using namespace world;
using namespace sf;

namespace render {
	class Renderer {
	public:
		Renderer(RenderWindow& window, const Map& map, const Camera& camera);
		void renderFrame();
	private:
		RenderWindow& window;
		const Map& map;
		const Camera& camera;

		void drawMap();
		void visualiseHeightmap(RectangleShape& tileShape, const Tile& tile);
		void drawBuildings();
	};
} // namespace render
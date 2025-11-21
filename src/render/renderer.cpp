#include <SFML/Graphics.hpp>

#include "renderer.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"

using namespace world;
using namespace sf;

namespace render {
	Renderer::Renderer(RenderWindow& window, const Map& map, const Camera& camera)
		: window(window), map(map), camera(camera)
	{
	}

	void Renderer::renderFrame() {
		window.clear();
		window.setView(camera.createView(window));
		drawMap();
		drawBuildings();
		window.display();
	}
	
	void Renderer::drawMap() {

		Vector2f cameraPos = camera.getPosition();
		float cameraZoom = camera.getZoom();

		const float tileSize = 32.f; // Size of each tile in pixels
		RectangleShape tileShape(Vector2f(tileSize, tileSize) * cameraZoom);

		for (int y = 0; y < map.getSize().y; ++y) {
			for (int x = 0; x < map.getSize().x; ++x) {
				const Tile& tile = const_cast<Map&>(map).getTile(x, y);

				switch (tile.type) {
					case TileType::Ground:
						tileShape.setFillColor(Color(34, 139, 34)); // Green
						break;
					case TileType::Water:
						tileShape.setFillColor(Color(30, 144, 255)); // Blue
						break;
					case TileType::Mountain:
						tileShape.setFillColor(Color(139, 137, 137)); // Gray
						break;
				}

				Vector2f tileWorldPos{
					static_cast<float>(x) * tileSize,
					static_cast<float>(y) * tileSize
				};

				Vector2f tileScreenPos = (tileWorldPos - cameraPos);

				tileShape.setPosition(tileScreenPos);

				window.draw(tileShape);
			}
		}
	}
	
	void Renderer::drawBuildings() {
		// Implementation for drawing buildings
	}
} // namespace render
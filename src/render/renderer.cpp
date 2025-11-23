#include <SFML/Graphics.hpp>

#include "renderer.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"
#include "constants.hpp"

using namespace world;
using namespace sf;

namespace render {
	Renderer::Renderer(
		RenderWindow& window,
		const Map& map,
		const Camera& camera,
		const InputManager& inputManager
	)
		: window(window),
		map(map),
		camera(camera),
		inputManager(inputManager)
	{
	}

	void Renderer::renderFrame() {
		window.clear();
		window.setView(camera.createView(window));
		drawMap();
		drawBuildings();
		drawMouseHoverTile();
		window.display();
	}
	
	/// @attention: Only draw objects in world-space
	void Renderer::drawMap() {

		const float tileSize = TILE_SIZE; // Size of each tile in pixels
		RectangleShape tileShape(Vector2f(tileSize, tileSize));

		for (int y = 0; y < map.getSize().y; ++y) {
			for (int x = 0; x < map.getSize().x; ++x) {
				const Tile* tilePtr = map.getTile(x, y);
				if (tilePtr == nullptr) {
					continue;
				}
				const Tile& tile = *tilePtr;

				switch (tile.getType()) {
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

				tileShape.setPosition({
					static_cast<float>(x) * tileSize,
					static_cast<float>(y) * tileSize
				});

				window.draw(tileShape);
			}
		}
	}

	/// @brief Debug function to visualise heightmap, should be called from drawMap()
	void Renderer::visualiseHeightmap(RectangleShape& tileShape, const Tile& tile) {
		// Greyscale heightmap visualisation
		int height = tile.getHeight();
		tileShape.setFillColor(Color(
			(height + 2) * (255 / 4.f),
			(height + 2) * (255 / 4.f),
			(height + 2) * (255 / 4.f)));
	}
	
	void Renderer::drawBuildings() {
		// Implementation for drawing buildings
	}

	void Renderer::drawMouseHoverTile() {
		const Tile* tilePtr = inputManager.getMouseHoverTile(window, camera, map);
		if (tilePtr == nullptr) {
			return;
		}
		const Tile& tile = *tilePtr;

		RectangleShape hoverShape(Vector2f(TILE_SIZE, TILE_SIZE));
		hoverShape.setFillColor(Color(0, 0, 0, 100)); // Semi-transparent black
		hoverShape.setPosition(Vector2f(
			tile.getPosition().x * TILE_SIZE,
			tile.getPosition().y * TILE_SIZE
		));
		window.draw(hoverShape);
	}
} // namespace render
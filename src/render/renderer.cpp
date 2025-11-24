#include "renderer.hpp"

#include <SFML/Graphics.hpp>

#include "world/map.hpp"
#include "world/camera.hpp"
#include "constants.hpp"
#include "ui/ui_manager.hpp"

using namespace world;
using namespace sf;
using namespace ui;

namespace render {
	Renderer::Renderer(
		RenderWindow& window,
		const Map& map,
		const Camera& camera,
		const InputManager& inputManager,
		const UiManager& uiManager
	) : 
		window(window),
		map(map),
		camera(camera),
		inputManager(inputManager),
		uiManager(uiManager)
	{}

	void Renderer::renderFrame() {
		window.clear();
		window.setView(camera.createView(window));
		drawMap();
		drawMouseHoverTile();
		drawUi();
		window.display();
	}
	
	/// @attention: Only draw objects in world-space
	void Renderer::drawMap() {

		RectangleShape tileShape(Vector2f(TILE_SIZE, TILE_SIZE));
		RectangleShape buildingShape(Vector2f(TILE_SIZE, TILE_SIZE));

		for (int y = 0; y < map.getSize().y; ++y) {
			for (int x = 0; x < map.getSize().x; ++x) {

				// Draw tile

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
					static_cast<float>(x) * TILE_SIZE,
					static_cast<float>(y) * TILE_SIZE
				});

				window.draw(tileShape);

				// Draw building

				const Building* buildingPtr = tile.getBuilding();
				if (buildingPtr == nullptr) {
					continue;
				}
				const Building& building = *buildingPtr;

				buildingShape.setFillColor(building.prefab.buildingCategory.color);
				buildingShape.setPosition(tileShape.getPosition());

				window.draw(buildingShape);
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

	void Renderer::drawMouseHoverTile() const {
		const Tile* tilePtr = inputManager.getMouseHoverTile();
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

	void Renderer::drawUi() const {
		window.setView(window.getDefaultView());
		uiManager.draw(window);
	}
}
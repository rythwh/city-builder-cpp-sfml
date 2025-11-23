#pragma once

#include <SFML/Graphics.hpp>

#include "world/map.hpp"
#include "world/camera.hpp"
#include "core/input.hpp"
#include "ui/ui_manager.hpp"

using namespace world;
using namespace sf;
using namespace core;
using namespace ui;

namespace render {
	class Renderer {
	public:
		Renderer(
			RenderWindow& window,
			const Map& map,
			const Camera& camera,
			const InputManager& inputManager,
			const UiManager& uiManager
		);
		void renderFrame();
	private:
		RenderWindow& window;
		const Map& map;
		const Camera& camera;
		const InputManager& inputManager;
		const UiManager& uiManager;

		void drawMap();
		void visualiseHeightmap(RectangleShape& tileShape, const Tile& tile);
		void drawBuildings();
		void drawMouseHoverTile() const;

		void drawUi() const;
	};
}
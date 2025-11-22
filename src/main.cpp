#include <SFML/Graphics.hpp>
#include <optional>

#include "utils/window_utils.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"
#include "render/renderer.hpp"
#include "constants.hpp"
#include "core/input.hpp"
#include "core/state.hpp"

using namespace world;
using namespace render;
using namespace sf;
using namespace core;

int main()
{
	auto window = RenderWindow(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "City Builder");
	window.setFramerateLimit(FRAME_RATE_LIMIT);
	utils::placeWindowOnScreen(window);

	Vector2i mapSize{MAP_WIDTH, MAP_HEIGHT};
	Map map(mapSize.x, mapSize.y);
	Camera camera(mapSize);
	core::GameState gameState{};

	Renderer renderer(window, map, camera);

	while (window.isOpen())
	{
		while (const std::optional<Event> event = window.pollEvent())
		{
			// Close window with X-button
			if (event->is<Event::Closed>())
			{
				window.close();
			}

			processInput(event, gameState, window, camera, map);
		}

		renderer.renderFrame();
	}
}
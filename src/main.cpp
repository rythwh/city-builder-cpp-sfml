#include <SFML/Graphics.hpp>
#include <optional>

#include "utils/window_utils.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"
#include "render/renderer.hpp"
#include "constants.hpp"
#include "core/input.hpp"
#include "core/state.hpp"
#include "core/time.hpp"

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

	Map map(mapSize);
	Camera camera(mapSize);

	StateManager stateManager{};
	TimeManager timeManager{};
	InputManager inputManager(stateManager, window, camera, map, timeManager);

	Renderer renderer(window, map, camera, inputManager);

	while (window.isOpen())
	{
		timeManager.calculateDeltaTime();

		while (const std::optional<Event> event = window.pollEvent())
		{
			// Close window with X-button
			if (event->is<Event::Closed>())
			{
				window.close();
			}

			inputManager.update(event);
		}

		renderer.renderFrame();

		inputManager.reset();
	}
}
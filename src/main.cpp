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
#include "sim/city.hpp"

using namespace world;
using namespace render;
using namespace sf;
using namespace core;
using namespace sim;

int main()
{
	auto window = RenderWindow(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "City Builder");
	window.setFramerateLimit(FRAME_RATE_LIMIT);
	utils::placeWindowOnScreen(window);

	constexpr Vector2i mapSize{MAP_WIDTH, MAP_HEIGHT};

	Map map(mapSize);
	City city{};
	Camera camera(mapSize);

	StateManager stateManager{};
	TimeManager timeManager{};
	UiManager uiManager(window.getSize());
	InputManager inputManager(stateManager, window, camera, map, timeManager, uiManager, city);

	Renderer renderer(window, map, camera, inputManager, uiManager);

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
	}
}
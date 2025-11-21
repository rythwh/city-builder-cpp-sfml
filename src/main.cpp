#include <SFML/Graphics.hpp>
#include <optional>

#include "utils/window_utils.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"
#include "render/renderer.hpp"

using namespace world;
using namespace render;
using namespace sf;

int main()
{
	auto window = RenderWindow(VideoMode({1920u, 1080u}), "City Builder");
	window.setFramerateLimit(144);
	utils::placeWindowOnScreen(window);

	Vector2i mapSize{50, 30};
	Map map(mapSize.x, mapSize.y);
	Camera camera(mapSize);

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

			// Close window with Escape key
			if (const auto* keyPressed = event->getIf<Event::KeyPressed>())
			{
				if (keyPressed->scancode == Keyboard::Scan::Escape)
				{
					window.close();
				}
			}
		}

		renderer.renderFrame();
	}
}
#include <SFML/Graphics.hpp>
#include <optional>

#include "utils/window_utils.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"
#include "render/renderer.hpp"
#include "constants.hpp"

using namespace world;
using namespace render;
using namespace sf;

int main()
{
	auto window = RenderWindow(VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "City Builder");
	window.setFramerateLimit(FRAME_RATE_LIMIT);
	utils::placeWindowOnScreen(window);

	Vector2i mapSize{MAP_WIDTH, MAP_HEIGHT};
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
				switch (keyPressed->scancode)
				{
				case Keyboard::Scan::Escape:
					window.close();
					break;
				case Keyboard::Scan::W:
					camera.move(0.f, -10.f);
					break;
				case Keyboard::Scan::S:
					camera.move(0.f, 10.f);
					break;
				case Keyboard::Scan::A:
					camera.move(-10.f, 0.f);
					break;
				case Keyboard::Scan::D:
					camera.move(10.f, 0.f);
					break;
				}
			}
			if (const auto* mouseWheel = event->getIf<Event::MouseWheelScrolled>())
			{
				if (mouseWheel->wheel == Mouse::Wheel::Vertical)
				{
					float delta = mouseWheel->delta;
					float newZoom = camera.getZoom() - delta * 0.1f;
					camera.setZoom(newZoom);
				}
			}
		}

		renderer.renderFrame();
	}
}
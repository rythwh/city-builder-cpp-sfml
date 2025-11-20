#include <SFML/Graphics.hpp>
#include <optional>

#include "window_utils.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "City Builder");
    window.setFramerateLimit(144);
    window_utils::placeWindowOnScreen(window);

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            // Close window with X-button
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // Close window with Escape key
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear();
        window.display();
    }
}
#include "window_utils.hpp"

namespace utils {
	void placeWindowOnScreen(sf::RenderWindow& window)
	{
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		sf::Vector2u windowSize = window.getSize();

		sf::Vector2i centerPos{
			0,0
		};

		window.setPosition(centerPos);
	}
}
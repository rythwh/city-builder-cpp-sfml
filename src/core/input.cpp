#include "input.hpp"

#include <optional>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "state.hpp"
#include "constants.hpp"
#include "world/tile.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"

using namespace sf;
using namespace world;

namespace core {

	void InputManager::processInput(
		std::optional<Event> inputEvent,
		core::GameState& gameState,
		RenderWindow& window,
		Camera& camera,
		Map& map
	) {
		if (const auto* keyPressed = inputEvent->getIf<Event::KeyPressed>())
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
			case Keyboard::Scan::R:
				if (gameState.getMode() == GameState::Mode::Road) {
					gameState.setMode(GameState::Mode::None);
				} else {
					gameState.setMode(GameState::Mode::Road);
				}
				break;
			case Keyboard::Scan::B:
				if (gameState.getMode() == GameState::Mode::Build) {
					gameState.setMode(GameState::Mode::None);
				} else {
					gameState.setMode(GameState::Mode::Build);
				}
				break;
			case Keyboard::Scan::Z:
				if (gameState.getMode() == GameState::Mode::Demolish) {
					gameState.setMode(GameState::Mode::None);
				} else {
					gameState.setMode(GameState::Mode::Demolish);
				}
				break;
			}
		}
		if (const auto* mouseWheel = inputEvent->getIf<Event::MouseWheelScrolled>())
		{
			if (mouseWheel->wheel == Mouse::Wheel::Vertical)
			{
				float delta = mouseWheel->delta;
				float newZoom = camera.getZoom() - delta * 0.1f;
				camera.setZoom(newZoom);
			}
		}
		if (const auto* mouseButton = inputEvent->getIf<Event::MouseButtonPressed>())
		{
			if (mouseButton->button == Mouse::Button::Left)
			{
				Tile* tilePtr = getMouseHoverTile(window, camera, map);
				if (tilePtr == nullptr) {
					return;
				}
				Tile& tile = *tilePtr;

				// Handle left-click on tile based on current mode
					switch (gameState.getMode()) {
						case GameState::Mode::Road:
							std::cout << "Place road at (" << tile.getPosition().x << ", " << tile.getPosition().y << ")" << std::endl;
							break;
						case GameState::Mode::Build:
							std::cout << "Place building at (" << tile.getPosition().x << ", " << tile.getPosition().y << ")" << std::endl;
							break;
						case GameState::Mode::Demolish:
							std::cout << "Demolish object at (" << tile.getPosition().x << ", " << tile.getPosition().y << ")" << std::endl;
							break;
						default:
							std::cout << "Clicked on tile at (" << tile.getPosition().x << ", " << tile.getPosition().y << ")" << std::endl;
							break;
					}
			}
		}
	}

	const Tile* InputManager::getMouseHoverTile(
		const RenderWindow& window,
		const Camera& camera,
		const Map& map) const
	{
		if (cachedMouseHoverTile != nullptr) {
			return cachedMouseHoverTile;
		}

		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f worldPos = window.mapPixelToCoords(mousePos, camera.createView(window));

		int tileX = static_cast<int>(worldPos.x) / TILE_SIZE;
		int tileY = static_cast<int>(worldPos.y) / TILE_SIZE;

		// Clamp to map bounds
		if (tileX < 0) {
			return nullptr;
		}
		if (tileY < 0) {
			return nullptr;
		}
		if (tileX >= map.getSize().x) {
			return nullptr;
		}
		if (tileY >= map.getSize().y) {
			return nullptr;
		}

		return map.getTile(tileX, tileY);
	}

	Tile* InputManager::getMouseHoverTile(
		const RenderWindow& window,
		const Camera& camera,
		Map& map
	) {
		return const_cast<Tile*>(
			getMouseHoverTile(
				window,
				camera,
				const_cast<const Map&>(map)
			)
		);
	}
} // namespace core
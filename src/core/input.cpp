#include "input.hpp"

#include <optional>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "state.hpp"
#include "constants.hpp"
#include "world/tile.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"
#include "core/time.hpp"

using namespace sf;
using namespace world;

namespace core {

	InputManager::InputManager(
		StateManager& stateManager,
		RenderWindow& window,
		Camera& camera,
		Map& map,
		TimeManager& timeManager
	) : 
		stateManager(stateManager),
		window(window),
		camera(camera),
		map(map),
		timeManager(timeManager)
	{
		update(std::nullopt);
	};

	void InputManager::update(std::optional<Event> inputEvent) {
		processMovementInput();
		processInput(inputEvent);
	}

	void InputManager::processMovementInput() {
		float deltaTime = timeManager.getDeltaTime();
		float zoom = camera.getZoom();

		Vector2f movementDelta{0.f, 0.f};
		if (Keyboard::isKeyPressed(Keyboard::Scan::W)) {
			movementDelta.y -= CAMERA_SPEED;
		}
		if (Keyboard::isKeyPressed(Keyboard::Scan::S)) {
			movementDelta.y += CAMERA_SPEED;
		}
		if (Keyboard::isKeyPressed(Keyboard::Scan::A)) {
			movementDelta.x -= CAMERA_SPEED;
		}
		if (Keyboard::isKeyPressed(Keyboard::Scan::D)) {
			movementDelta.x += CAMERA_SPEED;
		}
		movementDelta *= zoom * deltaTime;
		camera.move(movementDelta);
	}

	void InputManager::processInput(std::optional<Event> inputEvent) {
		if (const auto* keyPressed = inputEvent->getIf<Event::KeyPressed>())
		{
			switch (keyPressed->scancode)
			{
			case Keyboard::Scan::Escape:
				window.close();
				break;
			case Keyboard::Scan::R:
				if (stateManager.getMode() == StateManager::Mode::Road) {
					stateManager.setMode(StateManager::Mode::None);
				} else {
					stateManager.setMode(StateManager::Mode::Road);
				}
				break;
			case Keyboard::Scan::B:
				if (stateManager.getMode() == StateManager::Mode::Build) {
					stateManager.setMode(StateManager::Mode::None);
				} else {
					stateManager.setMode(StateManager::Mode::Build);
				}
				break;
			case Keyboard::Scan::Z:
				if (stateManager.getMode() == StateManager::Mode::Demolish) {
					stateManager.setMode(StateManager::Mode::None);
				} else {
					stateManager.setMode(StateManager::Mode::Demolish);
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
		
	}

	void InputManager::processMouseClick(std::optional<Event> inputEvent) {
		if (const auto* mouseButton = inputEvent->getIf<Event::MouseButtonPressed>())
		{
			if (mouseButton->button == Mouse::Button::Left)
			{
				Tile* tilePtr = getMouseHoverTile();
				if (tilePtr == nullptr) {
					return;
				}
				Tile& tile = *tilePtr;

				// Handle left-click on tile based on current mode
					switch (stateManager.getMode()) {
						case StateManager::Mode::Road:
							std::cout << "Place road at (" << tile.getPosition().x << ", " << tile.getPosition().y << ")" << std::endl;
							break;
						case StateManager::Mode::Build:
							std::cout << "Place building at (" << tile.getPosition().x << ", " << tile.getPosition().y << ")" << std::endl;
							break;
						case StateManager::Mode::Demolish:
							std::cout << "Demolish object at (" << tile.getPosition().x << ", " << tile.getPosition().y << ")" << std::endl;
							break;
						default:
							std::cout << "Clicked on tile at (" << tile.getPosition().x << ", " << tile.getPosition().y << ")" << std::endl;
							break;
					}
			}
		}
	}

	const Tile* InputManager::getMouseHoverTile() const
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

	Tile* InputManager::getMouseHoverTile() {
		return const_cast<Tile*>(
			static_cast<const InputManager*>(this)->getMouseHoverTile()
		);
	}
}
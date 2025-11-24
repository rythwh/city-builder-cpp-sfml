#include "input.hpp"

#include <optional>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "state.hpp"
#include "constants.hpp"
#include "world/tile.hpp"
#include "world/map.hpp"
#include "world/camera.hpp"
#include "core/time.hpp"
#include "ui/ui_manager.hpp"
#include "sim/building_prefab.hpp"
#include "sim/city.hpp"

using namespace sf;
using namespace world;
using namespace ui;
using namespace std;
using namespace sim;

namespace core {

	InputManager::InputManager(
		StateManager& stateManager,
		RenderWindow& window,
		Camera& camera,
		Map& map,
		TimeManager& timeManager,
		UiManager& uiManager,
		City& city
	) : 
		stateManager(stateManager),
		window(window),
		camera(camera),
		map(map),
		timeManager(timeManager),
		uiManager(uiManager),
		city(city)
	{
		update(nullopt);
	};

	void InputManager::update(const optional<Event>& inputEvent) const {
		processMovementInput();
		processInput(inputEvent);
		processMouseClick(inputEvent);
	}

	void InputManager::processMovementInput() const {
		const float deltaTime = timeManager.getDeltaTime();
		const float zoom = camera.getZoom();

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

	void InputManager::processInput(const optional<Event>& inputEvent) const {
		if (const auto* keyPressed = inputEvent->getIf<Event::KeyPressed>())
		{
			switch (keyPressed->scancode)
			{
			case Keyboard::Scan::Escape:
				window.close();
				break;
			case Keyboard::Scan::B:
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
				const float delta = mouseWheel->delta;
				const float newZoom = camera.getZoom() - delta * 0.1f;
				camera.setZoom(newZoom);
			}
		}
	}

	void InputManager::processMouseClick(const optional<Event>& inputEvent) const {
		if (const auto* mouseButton = inputEvent->getIf<Event::MouseButtonPressed>())
		{
			if (mouseButton->button == Mouse::Button::Left)
			{
				string_view elementId = uiManager.clickedElement(Mouse::getPosition(window));
				if (!elementId.empty()) {
					for (auto& buildingCategory : sim::buildingCategories) {
						if (elementId == buildingCategory.name) {
							stateManager.setMode(StateManager::Mode::Build);
							stateManager.setSelectedBuildingCategory(buildingCategory);
							cout << buildingCategory.name << endl;
							return;
						}
					}
				}

				const Tile* tilePtr = getMouseHoverTile();
				if (tilePtr == nullptr) {
					return;
				}
				const Tile& tile = *tilePtr;

				if (stateManager.getMode() == StateManager::Mode::Build && tile.getType() == TileType::Ground && tile.getBuilding() == nullptr) {
					for (const BuildingPrefab& prefab : buildingPrefabs) {
						if (prefab.buildingCategory.buildingCategory == stateManager.getSelectedBuildingCategory().buildingCategory) {
							Building building(prefab, BuildingDensity::Low, BuildingLevel::Level1);
							city.placeBuilding(building, const_cast<Tile&>(tile));
							return;
						}
					}
				}

				if (stateManager.getMode() == StateManager::Mode::Demolish && tile.getBuilding() != nullptr) {
					city.removeBuilding(const_cast<Tile&>(tile));
				}
			}
		}
	}

	const Tile* InputManager::getMouseHoverTile() const
	{
		const Vector2i mousePos = Mouse::getPosition(window);
		const Vector2f worldPos = window.mapPixelToCoords(mousePos, camera.createView(window));

		const int tileX = static_cast<int>(worldPos.x) / TILE_SIZE;
		const int tileY = static_cast<int>(worldPos.y) / TILE_SIZE;

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
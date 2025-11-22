#include <SFML/Graphics.hpp>
#include "camera.hpp"
#include "constants.hpp"

using namespace world;
using namespace sf;

namespace world {
	Camera::Camera(Vector2i mapSize) {
		position = (Vector2f(mapSize.x, mapSize.y) * static_cast<float>(TILE_SIZE)) / 2.f;
		zoom = 1.f;
	}

	void Camera::setPosition(float x, float y) {
		position = Vector2f(x, y);
	}

	void Camera::move(float deltaX, float deltaY) {
		position.x += deltaX;
		position.y += deltaY;
	}

	const Vector2f& Camera::getPosition() const {
		return position;
	}

	void Camera::setZoom(float newZoom) {
		zoom = newZoom;
		if (zoom < CAMERA_MIN_ZOOM) {
			zoom = CAMERA_MIN_ZOOM;
		} else if (zoom > CAMERA_MAX_ZOOM) {
			zoom = CAMERA_MAX_ZOOM;
		}
	}

	View Camera::createView(const RenderWindow& window) const {
		View view{};
		view.setSize(static_cast<Vector2f>(window.getSize()) * zoom);
		view.setCenter(position);
		return view;
	}
} // namespace world
#include <SFML/Graphics.hpp>
#include "camera.hpp"

using namespace world;
using namespace sf;

namespace world {
	Camera::Camera(Vector2i mapSize) {
		position = Vector2f(mapSize.x, mapSize.y) / 2.f;
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

	View Camera::createView(const RenderWindow& window) const {
		View view{};
		view.setSize(static_cast<Vector2f>(window.getSize()) * zoom);
		view.setCenter(position);
		return view;
	}
} // namespace world
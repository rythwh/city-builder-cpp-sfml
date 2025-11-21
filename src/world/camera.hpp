#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace world {
	class Camera
	{
	public:
		Camera(Vector2i mapSize);

		void setPosition(float x, float y);
		void move(float deltaX, float deltaY);

		const Vector2f& getPosition() const;
		const float getZoom() const { return zoom; }

		View createView(const RenderWindow& window) const;
	private:
		Vector2f position;
		float zoom;
	};
} // namespace world
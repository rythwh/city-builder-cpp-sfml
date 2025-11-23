#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace ui {
	class UiElement {
	public:
		virtual ~UiElement() = default;

		[[nodiscard]] virtual bool isHovered(Vector2i mousePos) const = 0;
		virtual void draw(RenderTarget& target) const = 0;

		[[nodiscard]] virtual Vector2f getPosition() const {
			return background.getPosition();
		}
	protected:
		RectangleShape background;
	};
}
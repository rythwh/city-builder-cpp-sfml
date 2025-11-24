#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace ui {
	class UiElement {
	public:
		virtual ~UiElement();

		[[nodiscard]] virtual std::string_view isHovered(Vector2i mousePos) const = 0;
		virtual void draw(RenderTarget& target) const = 0;

		[[nodiscard]] virtual Vector2f getPosition() const {
			return background.getPosition();
		}

		[[nodiscard]] virtual std::string_view getId() const = 0;
	protected:
		RectangleShape background;
	};

	inline UiElement::~UiElement() = default;
}

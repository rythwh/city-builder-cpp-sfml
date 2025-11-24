#pragma once

#include <SFML/Graphics.hpp>

#include "ui/ui_element.hpp"

using namespace sf;
using namespace std;

namespace ui {
	class UiButton : UiElement {
	public:
		UiButton(string_view str, Color colour, Vector2i position, Vector2i size, const UiElement& parent);
		[[nodiscard]] string_view isHovered(Vector2i mousePos) const override;
		void draw(RenderTarget &target) const override;
		[[nodiscard]] string_view getId() const override;

	protected:
		RectangleShape background;
		Text text;
	};
}
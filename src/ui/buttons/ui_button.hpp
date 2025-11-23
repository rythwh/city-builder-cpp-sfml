#pragma once

#include "ui/ui_element.hpp"

namespace ui {
	class UiButton : UiElement {
	public:
		UiButton(std::string_view str, Color colour, Vector2i position, Vector2i size, const UiElement& parent);
		[[nodiscard]] bool isHovered(Vector2i mousePos) const override;
		void draw(RenderTarget &target) const override;

	protected:
		RectangleShape background;
		Text text;
	};
}
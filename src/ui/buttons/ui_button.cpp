#include "ui_button.hpp"

#include "ui/ui_element.hpp"
#include "ui/ui_manager.hpp"

namespace ui {
	UiButton::UiButton(const std::string_view str, const Color colour, const Vector2i position, const Vector2i size, const UiElement& parent)
	:
	text(Text(font, std::string(str))),
	background(RectangleShape(Vector2f(size)))
	{
		const Vector2f adjustedPosition(Vector2f(position) + parent.getPosition());

		text.setCharacterSize(16);
		text.setPosition(adjustedPosition + Vector2f(5, 2));
		text.setFillColor(Color::Black);

		background.setPosition(adjustedPosition);
		background.setFillColor(colour);
	}

	bool UiButton::isHovered(const Vector2i mousePos) const {
		return background.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));
	}

	void UiButton::draw(RenderTarget& target) const {
		target.draw(background);
		target.draw(text);
	}
}

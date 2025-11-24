#include "ui_button.hpp"

#include <string>

#include "ui/ui_element.hpp"
#include "ui/ui_manager.hpp"

using namespace std;
using namespace sf;

namespace ui {
	UiButton::UiButton(const string_view str, const Color colour, const Vector2i position, const Vector2i size, const UiElement& parent)
	:
	text(Text(font, string(str))),
	background(RectangleShape(Vector2f(size)))
	{
		const Vector2f adjustedPosition(Vector2f(position) + parent.getPosition());

		text.setCharacterSize(16);
		text.setPosition(adjustedPosition + Vector2f(5, 2));
		text.setFillColor(Color::Black);

		background.setPosition(adjustedPosition);
		background.setFillColor(colour);
	}

	string_view UiButton::isHovered(const Vector2i mousePos) const {
		return background.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)) ? getId() : "";
	}

	void UiButton::draw(RenderTarget& target) const {
		target.draw(background);
		target.draw(text);
	}

	[[nodiscard]] string_view UiButton::getId() const {
		return string(text.getString());
	}
}

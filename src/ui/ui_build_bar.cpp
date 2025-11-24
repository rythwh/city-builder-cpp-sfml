#include "ui_build_bar.hpp"

#include <SFML/Graphics.hpp>

#include "buttons/ui_button.hpp"
#include "sim/building_prefab.hpp"

using namespace sf;

namespace ui {
	UiBuildBar::UiBuildBar(const Vector2u windowSize) {
		background.setSize(Vector2f(static_cast<float>(windowSize.x), 50.f));
		background.setFillColor(Color(50, 50, 50, 200));
		background.setPosition({0.f, static_cast<float>(windowSize.y) - 50.f});

		int buttonIndex = 0;
		for (auto [buildingCategory, name, colour] : sim::buildingCategories) {
			constexpr Vector2i buttonSize{100, 25};
			const Vector2i buttonPos{buttonSize.x * buttonIndex, 25};

			addBuildButton(UiButton(name, colour, buttonPos, buttonSize, *this));

			++buttonIndex;
		}
	}

	void UiBuildBar::addBuildButton(const UiButton& button) {
		buildButtons.push_back(button);
	}

	string_view UiBuildBar::isHovered(const Vector2i mousePos) const {
		for (UiButton button : buildButtons) {
			if (!button.isHovered(mousePos).empty()) {
				return button.getId();
			}
		}
		return background.getGlobalBounds().contains(static_cast<Vector2f>(mousePos)) ? getId() : "";
	}

	void UiBuildBar::draw(RenderTarget& target) const {
		target.draw(background);
		for (const auto& button : buildButtons) {
			button.draw(target);
		}
	}
}
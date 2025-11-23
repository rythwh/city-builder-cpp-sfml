#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "ui_element.hpp"
#include "buttons/ui_button.hpp"

using namespace sf;
using namespace std;

namespace ui {
	class UiBuildBar : public UiElement {
	public:
		explicit UiBuildBar(Vector2u windowSize);

		void addBuildButton(const UiButton& button);

		bool isHovered(Vector2i mousePos) const override;
		void draw(RenderTarget& target) const override;
	private:
		vector<UiButton> buildButtons;
	};

}
#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ui_element.hpp"

using namespace std;
using namespace sf;

namespace ui {

	inline Font font("../resources/fonts/arial.ttf");

	class UiManager {
	public:
		explicit UiManager(Vector2u windowSize);

		template <typename UiElementType, typename... Args>
		UiElementType& createElement(Args&&... args);

		void draw(RenderTarget& target) const;

	private:
		vector<unique_ptr<UiElement>> elements;
	};
}
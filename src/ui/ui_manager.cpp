#include "ui_manager.hpp"

#include "ui_build_bar.hpp"

using namespace sf;

namespace ui {

	UiManager::UiManager(const Vector2u windowSize) {
		createElement<UiBuildBar>(windowSize);
	}

	template <typename UiElementType, typename... Args>
	UiElementType& UiManager::createElement(Args&&... args) {
		unique_ptr<UiElementType> elementPtr = make_unique<UiElementType>(std::forward<Args>(args)...);
		UiElementType& elementRef = *elementPtr;
		elements.push_back(std::move(elementPtr));
		return elementRef;
	}

	void UiManager::draw(RenderTarget& target) const {
		for (const std::unique_ptr<UiElement>& element : elements) {
			element->draw(target);
		}
	}
}
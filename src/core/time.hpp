#pragma once

#include <SFML/System/Clock.hpp>

using namespace sf;

namespace core {

class TimeManager {
public:
	void calculateDeltaTime();

	[[nodiscard]] float getDeltaTime() const {
		return deltaTime;
	}
private:
	Clock clock{};
	float deltaTime{0.f};
};
}
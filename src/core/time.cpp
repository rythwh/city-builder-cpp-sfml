#include "time.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

using namespace sf;

namespace core {
	void TimeManager::calculateDeltaTime() {
		Time dt = clock.restart();
		deltaTime = dt.asSeconds();
	}
} // namespace core
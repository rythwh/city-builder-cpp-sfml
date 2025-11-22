#include <SFML/Graphics.hpp>

using namespace sf;

namespace sim {
	struct Building {
		int typeId;
		Vector2i position; // Position in tiles (x, y)
	};
}
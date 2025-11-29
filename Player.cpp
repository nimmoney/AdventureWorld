#include "Player.h"

Player::Player(const Point& point, const char(&the_keys)[NUM_KEYS + 1], Screen& theScreen)
	: screen(theScreen),
	prevPos(point)
{
	auto p = point;
	memcpy(keys, the_keys, NUM_KEYS * sizeof(keys[0]));
}

void Player::draw() {
	body.draw();
}

void Player::move() {
	if (atDoor) {
		body.draw();
		return;
	}
	body.draw(' ');

	prevPos = body;
	Point orig = body;
	body.move();

	if (screen.isWall(body))
		{
		body = orig;
	}
	
	body.draw();
}

void Player::handleKeyPressed(char key_pressed) {
	size_t index = 0;
	for (char k : keys) {
		if (std::tolower(k) == std::tolower(key_pressed)) {
			body.setDirection((Direction)index);
			return;
		}
		++index;
	}
}

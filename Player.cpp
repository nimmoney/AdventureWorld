#include "Player.h"

Player::Player(const Point& point, const char(&the_keys)[NUM_KEYS + 1], Screen& theScreen)
	: screen(theScreen) 
{
	for (auto& p : body) {
		p = point;
	}
	memcpy(keys, the_keys, NUM_KEYS * sizeof(keys[0]));
}

void Player::draw() {
	body->draw();
}

void Player::move() {
	if (atDoor) {
		body[0].draw();
		return;
	}
	body[0].draw(' ');

	Point orig = body[0];
	body[0].move();

	if (screen.isWall(body[0]))
		{
		body[0] = orig;
	}
	
	body[0].draw();
}

void Player::handleKeyPressed(char key_pressed) {
	size_t index = 0;
	for (char k : keys) {
		if (std::tolower(k) == std::tolower(key_pressed)) {
			body[0].setDirection((Direction)index);
			return;
		}
		++index;
	}
}

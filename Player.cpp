#include "Player.h"

Player::Player(const Point& point, const char(&the_keys)[NUM_KEYS + 1], Screen& theScreen)
	: body(point),
	screen(theScreen),
	prevPos(point)
{

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
	screen.drawCell(body);

	prevPos = body;
	Point orig = body;
	body.move();

	if (screen.isWall(body))
		{
		body = orig;
	}
	else if (screen.isObstacle(body)) {
		Direction dir = body.getDirection();
		Point obstaclePos = body;
		if (screen.canPushObstacle(obstaclePos, dir)) {
			screen.pushObstacle(obstaclePos, dir);
		}
		else body = orig;

	}
	else if (screen.isSwitch(body) && !screen.isSwitch(prevPos)) {
		screen.toggleSwitch(body);
		toggledSwitch = true;
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

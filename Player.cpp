#include "Player.h"
#include "Inventory.h"

Player::Player(const Point& point, const char(&move_keys)[NUM_KEYS + 1], char dropItemKey, Screen& theScreen)
	: body(point),
	  screen(theScreen),
	  prevPos(point),
	  dropItemKey(dropItemKey),
	  startPos(point)
{
	memcpy(moveKeys, move_keys, NUM_KEYS * sizeof(moveKeys[0]));
}

void Player::draw() {
	body.draw();
}

void Player::move() {
	if (moveDelay > 0) {
		moveDelay--;
		return;
	}
	moveDelay = MOVE_RATE; // reset delay

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
	key_pressed = std::tolower(key_pressed);

	// movement keys
	for (size_t i = 0; i < NUM_KEYS; ++i) {
		if (std::tolower(moveKeys[i]) == key_pressed) {
			body.setDirection((Direction)i);
			return;
		}
	}

	// item key
	if (key_pressed == std::tolower(dropItemKey)) {
		dropItem(screen);
		return;
	}
}

bool Player::dropItem(Screen& screen)
{
	if (items.isEmpty())
		return false;

	char itemChar = ' ';

	switch (items.getItem()) {
		case Inventory::typeItem::KEY: itemChar = 'K';
		break;
		default: return false;
		
	}

	screen.placeItemDown(body, itemChar);
	dropItem(); // calls void drop

	itemDroppedHere = true;
	
	return true;
}

#pragma once

#include "Point.h"
#include "Screen.h"

class Player {
	static constexpr int SIZE = 1;//remove
	static constexpr int NUM_KEYS = 5;
	Point body[SIZE];
	char keys[NUM_KEYS];
	Screen& screen;
	bool atDoor = false;

public:
	Player(const Point& point, const char(&the_keys)[NUM_KEYS + 1], Screen& theScreen);

	void draw();
	void move();
	void handleKeyPressed(char key);


	const Point& getPos() const { return body[0]; }
	void setPos(const Point& p) { body[0] = p;}
	bool isAtDoor() const { return atDoor; }
	void setAtDoor(bool val) { atDoor = val; }
};

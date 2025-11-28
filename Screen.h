#pragma once

#include <iostream>
#include "Point.h"

using std::cout, std::endl;

class Screen {
public:
	enum { MAX_X = 80, MAX_Y = 25 };
private:
	const char* screen[MAX_Y];
	char getCharAt(const Point& p) const {
		return screen[p.getY()][p.getX()];
	}
public:
	Screen(int level = 1);
	void loadLevel(int level);

	void draw() const;

	bool isWall(const Point& p) const {
		return getCharAt(p) == '#';
	}
	bool isDoor(const Point& p) const {
		char c = getCharAt(p);
		return (c >= '1' && c <= '9');
	}
	char getDoorNum(const Point& p) const {
		return getCharAt(p);
	}
};


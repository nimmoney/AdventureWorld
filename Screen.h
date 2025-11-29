#pragma once

#include <iostream>
#include "Point.h"

using std::cout, std::endl;

class Screen {
public:
	enum { MAX_X = 80, MAX_Y = 25 };
private:
	const char* screen[MAX_Y];
	bool itemTaken[MAX_Y][MAX_X] = { false };
	bool obstaclePresent[MAX_Y][MAX_X] = { false };

	char getCharAt(const Point& p) const {
		return screen[p.getY()][p.getX()];
	}
public:
	Screen(int level = 1);
	void loadLevel(int level);

	void draw() const;

	bool isWall(const Point& p) const { return getCharAt(p) == '#'; }

	// door
	char getDoorNum(const Point& p) const { return getCharAt(p); }
	bool isDoor(const Point& p) const {
		char c = getCharAt(p);
		return (c >= '1' && c <= '9');
	}

	//inventory
	bool isItem(const Point& p) const;
	char getItemChar(const Point& p) const;
	void clearPoint(const Point& p);

	// obstacle
	bool isObstacle(const Point& p) const;
	bool canPushObstacle(const Point& obstaclePos, const Direction dir) const;
	void pushObstacle(Point& obstaclePos, const Direction dir);
};


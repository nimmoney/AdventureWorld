#pragma once
#include <iostream>
#include "Point.h"
#include "GameUtils.h"

using std::cout, std::endl;
	
class Screen {
private:
	char screen[MAX_Y][MAX_X + 1];
	bool itemTaken[MAX_Y][MAX_X] = { false };
	bool obstaclePresent[MAX_Y][MAX_X] = { false };

	struct switchEffect {
		Point switchPos;
		Point wallPos; // wall that is affected by this switch
	};
	bool switchPresent[MAX_Y][MAX_X] = { false };
	bool switchState[MAX_Y][MAX_X] = { false }; // false(/): off, true(\): on

	char getCharAt(const Point& p) const {
		return screen[p.getY()][p.getX()];
	}
public:
	Screen(int level = 1);
	void loadLevel(int level);

	void draw() const;
	void drawCell(const Point& p) const;

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
	void placeItemDown(const Point& p, char item);

	// obstacle
	bool isObstacle(const Point& p) const;
	bool canPushObstacle(const Point& obstaclePos, const Direction dir) const;
	void pushObstacle(Point& obstaclePos, const Direction dir);

	// switch
	switchEffect switches[10];
	int numSwitches = 0;
	bool isSwitch(const Point& p) const;
	void toggleSwitch(const Point& p);
	void updateWallForSwitch(Point switchPos, Point wallPos);

	// riddle
	bool isRiddle(const Point& p) const { return getCharAt(p) == '?'; }
	void clearRiddle(const Point& p); // sets riddle tile to empty


};


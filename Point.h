#pragma once

#include <iostream>
#include "utils.h"
#include "Direction.h"

class Point {
	int x = 1, y = 1;
	int diff_x = 0, diff_y = 0;
	char ch = '*';
public:
	Point() {}
	constexpr Point(int x1, int y1, int diffx, int diffy, char c) {
		x = x1;
		y = y1;
		diff_x = diffx;
		diff_y = diffy;
		ch = c;
	}
	void draw() {
		draw(ch);
	}
	void draw(char c) {
		gotoxy(x, y);
		std::cout << c;
	}
	void move();
	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}

	void setDirection(Direction dir);
	Direction getDirection() const;
	void stop() {
		diff_x = 0;
		diff_y = 0;
	}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}

};


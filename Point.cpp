#include "Point.h"
#include "Screen.h"

void Point::move() {
	x = (x + diff_x + Screen::MAX_X) % Screen::MAX_X;
	y = (y + diff_y + Screen::MAX_Y) % Screen::MAX_Y;
}

void Point::setDirection(Direction dir) {
	switch (dir) {
	case Direction::UP:
		diff_x = 0;
		diff_y = -1;
		break;
	case Direction::RIGHT:
		diff_x = 1;
		diff_y = 0;
		break;
	case Direction::DOWN:
		diff_x = 0;
		diff_y = 1;
		break;
	case Direction::LEFT:
		diff_x = -1;
		diff_y = 0;
		break;
	case Direction::STAY:
		diff_x = 0;
		diff_y = 0;
		break;
	}
}

Direction Point::getDirection() const {
    if (diff_x == 0 && diff_y == 0) {
        return Direction::STAY;
    }
    if (diff_x != 0) {
        if (diff_x > 0) return Direction::RIGHT;
        else return Direction::LEFT;
    }

    if (diff_y > 0) return Direction::DOWN;
    if (diff_y < 0) return Direction::UP;

    return Direction::STAY;
}

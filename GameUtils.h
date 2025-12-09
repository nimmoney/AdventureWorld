#pragma once

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	STAY
};

//coords
constexpr int MAX_X = 80;
constexpr int MAX_Y = 25;
constexpr int MID_X = 30;
constexpr int MID_Y = 13;


constexpr int NUM_PLAYERS = 2;
constexpr int MAX_LEVEL = 2;
constexpr int LAST_LEVEL = 2;

constexpr int NUM_KEYS = 5;
enum Keys { ESC = 27 };


constexpr int MOVE_RATE = 1; // higher is slower

void gotoxy(int x, int y);
void hideCursor();
void cls();




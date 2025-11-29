#pragma once

#include "Point.h"
#include "Screen.h"
#include "inventory.h"

class Player {
	static constexpr int NUM_KEYS = 5;
	Point body;
	Point prevPos;
	char keys[NUM_KEYS];
	Screen& screen;

	bool atDoor = false;

	Inventory items;

public:
	Player(const Point& point, const char(&the_keys)[NUM_KEYS + 1], Screen& theScreen);

	void draw();
	void move();
	void handleKeyPressed(char key);

	//position
	const Point& getPos() const { return body; }
	Point& getPos() { return body; } // non const for calling setDirection
	void setPos(const Point& p) { body = p;}
	const Point& getPrevPos() const { return prevPos; }
	void stop() { body.stop(); }

	//door
	bool isAtDoor() const { return atDoor; }
	void setAtDoor(bool val) { atDoor = val; }

	//inventory
	bool hasItem() const { return items.getItem() != Inventory::typeItem::NONE; }
	bool hasKey() const { return items.getItem() == Inventory::typeItem::KEY; }
	void giveItem(Inventory::typeItem item) { items.setItem(item); }
	void dropItem() { items.setItem(Inventory::typeItem::NONE); }
};

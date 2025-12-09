#pragma once
#include "Point.h"
#include "GameUtils.h"
#include "Screen.h"
#include "Inventory.h"


class Player {
	char moveKeys[NUM_KEYS];
	char dropItemKey; // E, O for each player
	Screen& screen;
	int moveDelay = 0;  // counts down every "frame" (gameloop sleep) to control move rate
	
	Point body;
	Point prevPos;
	Point startPos;

	bool atDoor = false;
	Inventory items;
	


public:
	Player(const Point& startPoint, const char(&move_keys)[NUM_KEYS + 1], char dropItemKey, Screen& theScreen);

	void draw();
	void move();
	void handleKeyPressed(char key);

	//position
	const Point& getPos() const { return body; }
	Point& getPos() { return body; } // non const for calling setDirection
	void setPos(const Point& p) { body = p;}
	const Point& getPrevPos() const { return prevPos; }
	void stop() { body.stop(); }
	void sendToStart() { body = startPos; }

	//door
	bool isAtDoor() const { return atDoor; }
	void setAtDoor(bool val) { atDoor = val; }

	//inventory
	bool hasItem() const { return items.getItem() != Inventory::typeItem::NONE; }
	bool hasKey() const { return items.getItem() == Inventory::typeItem::KEY; }
	void giveItem(Inventory::typeItem item) { items.setItem(item); }
	void dropItem() { items.setItem(Inventory::typeItem::NONE); }
	bool dropItem(Screen& screen);
	bool itemDroppedHere = false;

	// switch
	bool toggledSwitch = false;
};

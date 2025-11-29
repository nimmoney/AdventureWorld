#pragma once

#include "Screen.h"
#include "Player.h"

class Game {
public:
    Game();
    void run();

private:
    void gameLoop();
    Screen screen;
    static const int NUM_PLAYERS = 2;
    Player players[NUM_PLAYERS];

    bool running = true;
    int currLevel = 0;

    // door
    bool firstPlayerAtDoor = false;
    void handleDoor(Player& player, int playerNum);
    bool bothAtDoor() const;
    int lastPlayerAtDoor = -1;

    // inventory
	void handleInventory(Player& player);


    void redrawScreen();
    void clearMiddle();
    void loadNextLevel();
    void returnToMenu();
    void resetGame();
    char mainMenu();
	void showInstructions();
    void pauseGame();
};

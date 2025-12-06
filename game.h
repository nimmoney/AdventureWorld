#pragma once

#include "Screen.h"
#include "Player.h"
#include "Riddle.h"

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

    // riddles
    const Riddle* levelRiddles = nullptr; // pointer to array of riddles for this level
    int numRiddlesInLevel = 0;
    int nextRiddleIndex = 0; // which riddle should be asked next
    int riddlesSolved = 0;
    void handleRiddles(Player& player);
    void handleRiddles(int level);
	void askRiddle(Player& player);


    void redrawScreen();
    void clearMiddle();
    void loadNextLevel();
    void returnToMenu();
    void resetGame();
    char mainMenu();
	void showInstructions();
    void pauseGame();

};

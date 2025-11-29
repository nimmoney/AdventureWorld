#include "Game.h"
#include "utils.h"
#include <conio.h>
#include <windows.h>

using std::flush;
enum Keys { ESC = 27 };
enum { MIDDLE_X = 30, MIDDLE_Y = 13 };
enum { MAX_LEVEL = 2 };
enum { MAX_X = 80, MAX_Y = 25 };
enum { numPlayers = 2 };

Game::Game()
    : screen(1),
    players{
        Player(Point(10, 10, 0, 0, '$'), "wdxas", screen),
        Player(Point(15, 5, 0, 0, '&'), "ilmjk", screen)
    }
{
    currLevel = 1;
}

void Game::run() {
    bool exitGame = false;

    while (!exitGame) {
        char choice = mainMenu();

        switch (choice) {
        case '1':
            gameLoop();
            break;
        case '8':
            showInstructions();
            break;
        case '9':
            exitGame = true;
            break;
        default:
            break;
        }
	}
}

void Game::gameLoop() {
    resetGame();
    hideCursor();
    screen.draw();

    for (auto& s : players) {
        s.draw();
    }

    running = true;

    while (running) {
        for (auto& s : players) {
            s.move();
        }
        for (int i = 0; i < numPlayers; i++) {
            handleDoor(players[i], i);
            handleInventory(players[i]);
        }
        if (bothAtDoor()) {
            if (players[0].hasKey() || players[1].hasKey() ) {
                clearMiddle();
                gotoxy(MIDDLE_X, MIDDLE_Y);
                cout << "Both players at doors! Level " << currLevel << " complete!" << flush;
                Sleep(1000);
                clearMiddle();
                redrawScreen();
                loadNextLevel();
            }
            else {
                if (lastPlayerAtDoor != -1) {
                    players[lastPlayerAtDoor].setPos(players[lastPlayerAtDoor].getPrevPos());
                    players[lastPlayerAtDoor].setAtDoor(false);
                    players[lastPlayerAtDoor].stop();
                }
                clearMiddle();
                gotoxy(MIDDLE_X, MIDDLE_Y);
                cout << "Both players at doors but no key!" << flush;
                Sleep(700);
                clearMiddle();
                redrawScreen();
            
            }
        }

        if (_kbhit()) {
            char key = _getch();
            if (key == Keys::ESC) pauseGame();
            else
                for (auto& s : players) s.handleKeyPressed(key);
        }

        Sleep(50);
    }

    cls();
}

void Game::handleDoor(Player& player, int playerNum) {

    if (player.isAtDoor()) {
        return;
	}

    const Point& pos = player.getPos();

    if (screen.isDoor(pos)) {
        char id = screen.getDoorNum(pos);
        player.setAtDoor(true);
        lastPlayerAtDoor = playerNum;
        if (!firstPlayerAtDoor) {
            firstPlayerAtDoor = true;
            clearMiddle(); 
            gotoxy(MIDDLE_X, MIDDLE_Y);
            cout << "Player stepped on door " << id << "!" << flush;
            Sleep(1000);
            clearMiddle();
            redrawScreen();
        }
    }
}

void Game:: handleInventory(Player& player) {
    const Point& pos = player.getPos();

    if (player.hasItem()) { return; }

    if (screen.isItem(pos))
    {
        char c = screen.getItemChar(pos);
        if (c == 'K')
            player.giveItem(Inventory::typeItem::KEY);
		screen.clearPoint(pos);
        clearMiddle();
        gotoxy(MIDDLE_X, MIDDLE_Y);
        cout << "Player picked up key!" << flush;
        Sleep(500);
        clearMiddle();
        redrawScreen();
    }
}
bool Game::bothAtDoor() const {
    for (const auto& player : players) {
        if (!player.isAtDoor())
            return false;
    }
    return true;
}

void Game::redrawScreen() {
    screen.draw();
    for (auto& s : players) {
        s.draw();
    }
}

void Game::clearMiddle() {
    gotoxy(0, MIDDLE_Y);
    for (int i = 0; i < MAX_X; ++i) cout << ' ';
    cout.flush();
}

char Game::mainMenu() {
    cls();
    hideCursor();
    gotoxy(0, 0);

    cout << "================= MAIN MENU =================" << endl;
    cout << "   (1) Start A New Game" << endl;
    cout << "   (8) Present Instructions and Keys" << endl;
    cout << "   (9) EXIT" << endl;
	cout << " Select an option: " << flush;
    return _getch();

}

void Game::showInstructions() {
    cls();
    gotoxy(0, 0);
    cout << "================= INSTRUCTIONS =================" << endl;
    cout << " Player 1 ($): W (up), A (left), S (down), D (right), X (stay)" << endl;
    cout << " Player 2 (&): I (up), J (left), K (down), L (right), M (stay)" << endl;
    cout << " Both players must reach their respective doors to complete the level." << endl;
    cout << " Press any key to return to the menu..." << flush;
    (void)_getch(); // void to ignore return val
}


void Game::loadNextLevel() {
    if (currLevel >= MAX_LEVEL) {
        clearMiddle();
        gotoxy(MIDDLE_X, MIDDLE_Y);
        cout << "=======THE END======" << flush;
		returnToMenu();
		return;
    }

    currLevel++;
	screen.loadLevel(currLevel);
	firstPlayerAtDoor = false;  

    for (auto& player : players) {
        player.setAtDoor(false);
    }
    players[0].setPos(Point(10, 10, 0, 0, '$'));
    players[1].setPos(Point(15, 5, 0, 0, '&'));

    screen.draw();
    for (auto& s : players) {
		s.draw();
	}
}

void Game::returnToMenu() {
	Sleep(500);
    running = false;
    cls();
}

void Game::resetGame() {
    currLevel = 1;
    firstPlayerAtDoor = false;
    screen.loadLevel(currLevel);
    for (auto& player : players) {
        player.setAtDoor(false);
        player.dropItem();
    }
    players[0].setPos(Point(10, 10, 0, 0, '$'));
    players[1].setPos(Point(15, 5, 0, 0, '&'));
}

void Game::pauseGame() {

    gotoxy(0, MIDDLE_Y);
    for (int i = 0; i < MAX_X; ++i) cout << ' ';

    gotoxy(MIDDLE_X, MIDDLE_Y);
    cout << "[ GAME PAUSED ]" << flush;

    gotoxy(MIDDLE_X - 10, MIDDLE_Y + 1);
    cout << "Press ESC to continue or H to return to menu" << flush;

    while (true) {
        if (_kbhit()) {
            char ch = _getch();

            if (ch == ESC) {
                clearMiddle();
                redrawScreen();
                return;
            }
            if (ch == 'H' || ch == 'h') {
                returnToMenu();
                return;
            }
        }
    }
}


#include "Game.h"
#include "GameUtils.h"

using std::flush;

constexpr Point startPosP1(3, 1, 0, 0, '$');
constexpr Point startPosP2(3, 2, 0, 0, '&');


Game::Game()
    : screen(1),
    players{
        Player(startPosP1, "wdxas", 'e', screen),
        Player(startPosP2, "ilmjk", 'o', screen)
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
    

    handleRiddles(currLevel);

    screen.draw(players, NUM_PLAYERS);

    for (auto& s : players) {
        s.draw();
    }

    running = true;

    while (running) {
        processInput();
        updatePlayers();
        updateTiles(); // inventory, riddles, doors

        if (visibilityDirty) {
            redrawScreen();
            visibilityDirty = false;
        }
        checkLevelComplete(); // both players at door? keys & riddles complete?

        Sleep(40);
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
            printMessage("Player arrived at door!");
            redrawScreen();
        }
    }
}

void Game::handleInventory(Player& player) {
    const Point& pos = player.getPos();

    if (player.itemDroppedHere) {
        if (!(player.getPos() == player.getPrevPos())) { // player moved
            player.itemDroppedHere = false;
        }
        return;

    }
    if (player.hasItem()) { return; }

    if (screen.isItem(pos))
    {
        char c = screen.getItemChar(pos);
        if (c == 'K') {
            player.giveItem(Inventory::typeItem::KEY);
            printMessage("Player picked up Key!", 1000);
        }
        if (c == '!') {
            player.giveItem(Inventory::typeItem::TORCH);
            visibilityDirty = true;
        }

        screen.clearPoint(pos);
        redrawScreen();
    }
}

void Game::handleRiddles(Player& player)
{
    if (numRiddlesInLevel == 0 || nextRiddleIndex >= numRiddlesInLevel)
        return;

    if (!screen.isRiddle(player.getPos()))
        return;

    askRiddle(player);
}

void Game::handleRiddles(int level)
{
    switch (level) {
    case 1:
        levelRiddles = RIDDLES_LEVEL1;
        numRiddlesInLevel = NUM_RIDDLES_LEVEL1;
        break;

    case 2:
        levelRiddles = RIDDLES_LEVEL2;
        numRiddlesInLevel = NUM_RIDDLES_LEVEL2;
        break;

    default:
        levelRiddles = nullptr;
        numRiddlesInLevel = 0;
        break;
    }

    nextRiddleIndex = 0;
    riddlesSolved = 0;
}

void Game::askRiddle(Player& player)
{
    const Riddle& r = levelRiddles[nextRiddleIndex];

    clearMiddle();
    gotoxy(15, 8);
    cout << r.getQuestion();

    for (int i = 0; i < 4; i++) {
        gotoxy(15, 10 + i);
        cout << (i + 1) << ") " << r.getAnswer(i);
    }

    cout.flush();

    char ans = 0;
    while (ans < '1' || ans > '4')
        ans = _getch();

    clearMiddle();
    gotoxy(15, 15);

    if ((ans - '1') == r.getCorrectAnswer()) {
        cout << "Correct!";
        Sleep(500);
        riddlesSolved++;
        screen.clearRiddle(player.getPos());
        nextRiddleIndex++;
        redrawScreen();
    }
    else {
        cout << "Wrong Answer! Try Again";
        Sleep(800);

        player.sendToStart();
        clearMiddle();
        redrawScreen();
        return;
    }

    Sleep(900);
}


bool Game::bothAtDoor() const {
    for (const auto& player : players) {
        if (!player.isAtDoor())
            return false;
    }
    return true;
}

void Game::updatePlayers()
{
    bool anyMoved = false;
    for (auto& s : players) {
        Point before = s.getPos();
        s.move();
        if (!(s.getPos() == before)) {
            anyMoved = true;
       }
    }
    if (anyMoved) {
        visibilityDirty = true;
    }
}


void Game::updateTiles()
{
    bool switchToggledThisFrame = false;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        handleDoor(players[i], i);
        handleInventory(players[i]);
        handleRiddles(players[i]);

        if (players[i].toggledSwitch) {
            switchToggledThisFrame = true;
            players[i].toggledSwitch = false;
        }
    }
    if (switchToggledThisFrame) {
        redrawScreen();
    }
}

void Game::processInput()
{
    if (!_kbhit())
        return;

    char key = _getch();
    if (key == Keys::ESC) {
        pauseGame();
        return;
    }

    for (auto& s : players)
        s.handleKeyPressed(key);
}

void Game::checkLevelComplete()
{
    if (!bothAtDoor())
        return;

    if ((players[0].hasKey() || players[1].hasKey()) && (riddlesSolved == numRiddlesInLevel)) {
        printMessage("Both players at door! Level Complete");
        redrawScreen();
        loadNextLevel();
    }
    else {
        if (lastPlayerAtDoor != -1) {
            players[lastPlayerAtDoor].setPos(players[lastPlayerAtDoor].getPrevPos());
            players[lastPlayerAtDoor].setAtDoor(false);
            players[lastPlayerAtDoor].stop();
        }

        if (!players[0].hasKey() && !players[1].hasKey()) {
            printMessage("Both players at door but no key!");
            redrawScreen();
        }

        if (riddlesSolved < numRiddlesInLevel) {
            printMessage("Solve all riddles to proceed!");
            redrawScreen();
        }
    }
}

void Game::redrawScreen() {
    screen.draw(players,NUM_PLAYERS);
    for (auto& s : players)
        s.draw();
}

void Game::clearMiddle() {
    gotoxy(0, MID_Y);
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
    cout << " Player 1 ($): W (up), A (left), S (down), D (right), X (stay), E (drop item)" << endl;
    cout << " Player 2 (&): I (up), J (left), K (down), L (right), M (stay), O (drop item)" << endl;
    cout << endl << " Both players must reach the door(1-9) to proceed to the next level." << endl;
    cout << " You will advance only if you have answered the riddles(?)" << endl;
    cout << " and collected the door key(K)." << endl;
    cout << " Tip: Try flipping switches to open hidden doors." << endl;
    cout << endl << " Press any key to return to the menu..." << flush;
    (void)_getch();
}

void Game::loadNextLevel() {
    if (currLevel >= MAX_LEVEL) {
        printMessage("========THE END======", 2000);
        cout << flush;
        returnToMenu();
        return;
    }

    currLevel++;
    screen.loadLevel(currLevel);
    handleRiddles(currLevel);

    firstPlayerAtDoor = false;

    for (auto& player : players) {
        players->dropItem();
        player.setAtDoor(false);
    }

    players[0].setPos(startPosP1);
    players[1].setPos(startPosP2);

    screen.draw(players, NUM_PLAYERS);
    for (auto& s : players)
        s.draw();
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

    players[0].setPos(startPosP1);
    players[1].setPos(startPosP2);
}

void Game::pauseGame() {

    gotoxy(0, MID_Y);
    for (int i = 0; i < MAX_X; ++i) cout << ' ';

    gotoxy(MID_X, MID_Y);
    cout << "[ GAME PAUSED ]" << flush;

    gotoxy(MID_X - 10, MID_Y + 1);
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

void Game::printMessage(const char* text, int delay)
{
    int boxWidth = strlen(text) + 6;
    int boxHeight = 5;

    int startX = (MAX_X - boxWidth) / 2;
    int startY = (MAX_Y - boxHeight) / 2;

    gotoxy(startX, startY);
    cout << '+';
    for (auto i = 0; i < (boxWidth - 2); ++i) cout << '=';
    cout << '+';

    gotoxy(startX, startY + 1);
    cout << '|';
    for (auto i = 0; i < (boxWidth - 2); ++i) cout << ' ';
    cout << '|';

    gotoxy(startX, startY + 2);
    cout << "|  " << text << "  |";

    gotoxy(startX, startY + 4);
    cout << '+';
    for (auto i = 0; i < (boxWidth - 2); ++i) cout << '=';
    cout << '+';

    cout.flush();
    Sleep(delay);

    // clear box

    for (auto y = 0; y < boxHeight; ++y) {
        gotoxy(startX, startY + y);
        for (auto i = 0; i < boxWidth; ++i)
            cout << ' ';
    }
    cout.flush();
}

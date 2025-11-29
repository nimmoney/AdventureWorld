#include "Screen.h"
#include "utils.h"




static const char* LEVEL1[Screen::MAX_Y] = {
//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"################################################################################", // 0
	"#############################                                          #    ####", // 1
	"#####               #########                                          #    ####", // 2
	"#####                                                                  #    ####", // 3
	"#####                           0                                      #    ####", // 4
	"#####                                                                  #    ####", // 5
	"#####                                                                  #    ####", // 6
	"#####                                                                       ####", // 7
	"#####               #########                                               ####", // 8
	"#####               #########                                               ####", // 9
	"#####                               K                                       1   ", // 10
	"#############################                                               ####", // 11
	"#############################                                               ####", // 12
	"#############################                                          #    ####", // 13
	"#############################                                          #    ####", // 14
	"#####################################     ##############################    ####", // 15
	"###################################                     ################    ####", // 16
	"###################################                     ################    ####", // 17
	"###################################                     ################    ####", // 18
	"###################################                                         ####", // 19
	"###################################                     ################    ####", // 20
	"###################################                     ################    ####", // 21
	"########################################################################    ####", // 22
	"########################################################################    ####", // 23
	"################################################################################"  // 24
};
static const char* LEVEL2[Screen::MAX_Y] = {
	//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"################################################################################", // 0
		"#############################                                          #    ####", // 1
		"#####               #########                                          #    ####", // 2
		"#####                                                                  #    ####", // 3
		"#####                                                                  #    ####", // 4
		"#####                                                                  #    ####", // 5
		"#####                                                                  #    ####", // 6
		"#####                                                                       ####", // 7
		"#####               #########                                               ####", // 8
		"#####               #########                                               ####", // 9
		"#####                                                                       2   ", // 10
		"#############################                                               ####", // 11
		"#############################                                               ####", // 12
		"#############################                            K             #    ####", // 13
		"#############################                                          #    ####", // 14
		"#####################################     ##############################    ####", // 15
		"###################################                     ################    ####", // 16
		"###################################                     ################    ####", // 17
		"###################################                     ################    ####", // 18
		"###################################                                         ####", // 19
		"###################################                     ################    ####", // 20
		"###################################                     ################    ####", // 21
		"########################################################################    ####", // 22
		"########################################################################    ####", // 23
		"################################################################################"  // 24
};

Screen::Screen(int level) {	loadLevel(level); }

void Screen::loadLevel(int level) {
	const char* const* numLevel = nullptr;
	switch (level) {
		case 1:
			numLevel = LEVEL1;
			break;
		case 2:
			numLevel = LEVEL2;
			break;
		default:
			numLevel = LEVEL1;
			break;
	}

	for (int y = 0; y < MAX_Y; ++y){
		screen[y] = numLevel[y];
		for (int x = 0; x < MAX_X; ++x) {
			itemTaken[y][x] = false;
			obstaclePresent[y][x] = (screen[y][x] == '0');
		}
	}
}
bool Screen::isItem(const Point& p) const {
	int x = p.getX();
	int y = p.getY();
	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
		return false;

	if (itemTaken[y][x])
		return false;

	char c = screen[y][x];
	// add more items in future
	return (c == 'K');
}

char Screen::getItemChar(const Point& p) const {
	int x = p.getX();
	int y = p.getY();

	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
		return ' ';

	return screen[y][x];
}

void Screen::clearPoint(const Point& p) {
	int x = p.getX();
	int y = p.getY();

	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
		return;

	itemTaken[y][x] = true; 
}

bool Screen::isObstacle(const Point& p) const
{
	int x = p.getX();
	int y = p.getY();
	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
		return false;
	
	return obstaclePresent[y][x];
}

bool Screen::canPushObstacle(const Point& obstaclePos, const Direction dir) const
{
	int x = obstaclePos.getX();
	int y = obstaclePos.getY();
	switch (dir) {
	case Direction::UP:
		y -= 1;
		break;
	case Direction::RIGHT:
		x += 1;
		break;
	case Direction::DOWN:
		y += 1;
		break;
	case Direction::LEFT:
		x -= 1;
		break;
	default:
		return false;
	}
	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
		return false;

	if (obstaclePresent[y][x])
		return false;
	char c = screen[y][x];

	if (c == '#')	
		return false;
	if (c >= '1' && c <= '9') 
		return false;
	if (c == 'K') 
		return false;
	return (c == ' ');
}

void Screen::pushObstacle(Point& obstaclePos, const Direction dir)
{
	int x = obstaclePos.getX();
	int y = obstaclePos.getY();
	int newX = x;
	int newY = y;
	switch (dir) {
	case Direction::UP:
		newY -= 1;
		break;
	case Direction::RIGHT:
		newX += 1;
		break;
	case Direction::DOWN:
		newY += 1;
		break;
	case Direction::LEFT:
		newX -= 1;
		break;
	default:
		return;
	}
	if (newX < 0 || newX >= MAX_X || newY < 0 || newY >= MAX_Y)
		return;
	if (!canPushObstacle(obstaclePos, dir))
		return;

	obstaclePresent[y][x] = false;
	obstaclePresent[newY][newX] = true;
	obstaclePos = Point(newX, newY, 0, 0, '0');

	// erase old obstacle and draw new one
	gotoxy(x, y);
	cout << ' ';
	gotoxy(newX, newY);
	cout << '0';
	cout.flush();
}


void Screen::draw() const {
	cls();

	for (int y = 0; y < MAX_Y; ++y) {
		gotoxy(0, y);
		for (int x = 0; x < MAX_X; ++x) {
			char c = screen[y][x];
			if (itemTaken[y][x] && (c == 'K') ) { // later: add other items
				c = ' ';
			}
			if (c == '0' && !obstaclePresent[y][x]) {
				c = ' ';
			}
			if (obstaclePresent[y][x]) { c = '0'; }
			cout << c;
		}
	}
	cout.flush();
}



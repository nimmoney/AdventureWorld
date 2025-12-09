#include "Screen.h"
#include "GameUtils.h"

static const char* LEVEL1[MAX_Y] = {
	"################################################################################", // 0
	"#                                                                              #", // 1
	"#                                                                              #", // 2
	"###############0######################################################00########", // 3
	"#             #                                                                #", // 4
	"#             #                                                                #", // 5
	"#             #  ############################################################ ##",	// 6
	"########### # #                                                             # ##", // 7
	"#         # # #  ############################## ######################0#### # ##", // 8
	"# ####### # # #                                                             # ##", // 9
	"# ####### # # #                                                             # ##", // 10
	"# #     # # # #  ################## ##### # ###   ########### ########### # # ##", // 11
	"# # ### # # # #                   # #   # # ###   #           #         # # # ##", // 12
	"# # # # # # # # # # # # #   ?     # #   # # ###   #    /      #    K    # # # ##", // 13
	"# # # # # # # # # # # # #         # #   # # ###               #         # # # ##", // 14
	"# # # # # # # # # # # # ########### ### # # ### ########### # ########### # # ##", // 15
	"# # # # # # # # # # #               #   # # ###             #             # # ##", // 16
	"# # # # # # # # # # ################# ### # ############################# # # ##", // 17
	"# # # # # # # # #                                                         # # ##", // 18
	"########################################################000#####################", // 19
	"#                                                                              #", // 20
	"#                                                                         1    #", // 21
	"################################################################################", // 22
	"################################################################################",	// 23
	"################################################################################", // 24
//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
};

static const char* LEVEL2[MAX_Y] = {
	"################################################################################", // 0
	"#                                              # / #                           #", // 1
	"#                                                                              #", // 2
	"#00#############################################################################", // 3
	"#             #                   #          #                                 #", // 4
	"#             #                   #     ?   /#                                 #", // 5
	"#             #  ############################################################ ##",	// 6
	"#####  #### ###                                                             # ##", // 7
	"#         #   #  #############################  #####################00#### # ##", // 8
	"# ####### #   #                           #     #      #                  # # ##", // 9
	"# ####### # # #                           #     #   #  #                  # # ##", // 10
	"# #     # # # #0################### ##### # ### #   #  ###### ########### # # ##", // 11
	"# # ### #   # # #        ########## #   # # ### #   #       # #        K# # # ##", // 12
	"# # # # #   # # ####### ?########## # / # # ### #   #    /  # #         # # # ##", // 13
	"############# # ################### #   # # ###     #       # #         # # # ##", // 14
	"# # #       # # ################### ### # # ### ############# ########### # # ##", // 15
	"# # #     # # # #######             #   # # ###             #             #   ##", // 16
	"#   ##    #   # ##################### ##### ############################# # # ##", // 17
	"# # ##    # # # #                                                         # # ##", // 18
	"########00######################################################################", // 19
	"#                                                                              #", // 20
	"#    #                                                                         #", // 21
	"#2   #                                                                         #", // 22
	"################################################################################",	// 23
	"################################################################################", // 24
//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
};


Screen::Screen(int level) {	loadLevel(level); }

void Screen::loadLevel(int level) {
	const char* const* numLevel = nullptr;

	switch (level) {
		case 1:
			numLevel = LEVEL1;
			updateWallForSwitch(Point(55, 13, 0, 0, '/'), Point(62, 13, 0, 0, '#'));
			break;
		case 2:
			numLevel = LEVEL2;
			updateWallForSwitch(Point(49, 1, 0, 0, '/'), Point(40, 3, 0, 0, '#'));
			updateWallForSwitch(Point(44, 5, 0, 0, '/'), Point(34, 5, 0, 0, '#'));
			updateWallForSwitch(Point(38, 13, 0, 0, '/'), Point(16, 12, 0, 0, '#'));
			updateWallForSwitch(Point(57, 13, 0, 0, '/'), Point(62, 13, 0, 0, '#'));
			break;
		default:
			numLevel = LEVEL1;
			break;
	}

	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			screen[y][x] = numLevel[y][x];

			// reset item & obstacle state
			itemTaken[y][x] = false;
			obstaclePresent[y][x] = (numLevel[y][x] == '0');
			switchPresent[y][x] = (numLevel[y][x] == '/' || numLevel[y][x] == '\\');
			switchState[y][x] = (numLevel[y][x] == '\\');  // on if backslash
		}
		screen[y][MAX_X] = '\0'; // end row string
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

void Screen::placeItemDown(const Point& p, char item)
{
	int x = p.getX();
	int y = p.getY();

	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
		return;

	screen[y][x] = item; // place item on map
	itemTaken[y][x] = false; // mark tile as having item

	//redraw
	gotoxy(x, y);
	cout << item;
	cout.flush();
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

	for (int y = 0; y < MAX_Y; y++) {
		gotoxy(0, y);
		for (int x = 0; x < MAX_X; x++) {
			char c = screen[y][x];
			if (itemTaken[y][x] && c == 'K')
				c = ' ';
			if (obstaclePresent[y][x])
				c = '0';
			else if (c == '0')
				c = ' '; // remove ones not present
			if (switchPresent[y][x])
				c = (switchState[y][x] ? '\\' : '/');
			cout << c;
		}
	}
	cout.flush();
}

void Screen::drawCell(const Point& p) const {
	int x = p.getX();
	int y = p.getY();

	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
		return;

	char c = screen[y][x];

	// inventory
	if (itemTaken[y][x] && c == 'K') {
		c = ' ';
	}
	// obstacle
	if (c == '0' && !obstaclePresent[y][x]) {
		c = ' ';
	}
	if (obstaclePresent[y][x]) {
		c = '0';
	}

	// switch
	if (switchPresent[y][x]) {
		c = (switchState[y][x] ? '\\' : '/');
	}

	gotoxy(x, y);
	cout << c;
	cout.flush();
}


bool Screen::isSwitch(const Point& p) const {
	int x = p.getX();
	int y = p.getY();
	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
		return false;
	return switchPresent[y][x];
}

void Screen::toggleSwitch(const Point& p)
{
	int x = p.getX();
	int y = p.getY();

	if (!switchPresent[y][x])
		return;

	switchState[y][x] = !switchState[y][x];

	for (int i = 0; i < numSwitches; i++) {
		if (switches[i].switchPos == p) {
			Point wall = switches[i].wallPos;
			int wallX = wall.getX();
			int wallY = wall.getY();

			screen[wallY][wallX] = (switchState[y][x] ? ' ' : '#');

			gotoxy(wallX, wallY);
			cout << screen[wallY][wallX];
			cout.flush();
		}
	}

}

void Screen::updateWallForSwitch(Point switchPos, Point wallPos)
{
	switches[numSwitches] = { switchPos, wallPos };
	numSwitches++;
}

void Screen::clearRiddle(const Point& p)
{
	int x = p.getX();
	int y = p.getY();

	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
		return;

	screen[y][x] = ' ';

}



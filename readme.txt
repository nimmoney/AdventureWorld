Nimrod Eshar 211427117
Naama

Game Rules: 
	- A level ends only when both players reach the door
	- At least one player must hold the key to advance
	- All riddles must be answered before the door opens

Game Elements:
1. Key:
	- A player picks up a key by stepping over it
	- Can be dropped using the drop key
	- Key remains on ground until picked up again
	- A key is needed to proceed to the next level

2. Switch:
	- Two modes: / OFF and \ ON
	- Stepping on a switch changes its mode
	- Each switch may control the removal or placement of a wall elsewhere
	- Used to open hidden passages to keys, doors, etc

3. Obstacles: 
	- Can be pushed by a player in the direction of his movement
	- Blocked by walls and other obstacles
	- Used to reveal paths in the maze
	
4. Riddles: 
	- Multiple choice questions
	- Player must choose an answer using the keys 1-4
	- If wrong: player returns to start point of level
	- All riddles must be solved to finish a level

Class Structure:
	Game - controls the game loop, level transitions, riddle logic, game rules
	Screen - holds the board for each level, manages: walls, ostacles, switches, drawing the level
	Player - controls movement, player inventory, player interaction with different tiles
	Point - movement logic and x,y coord
	Inventory - stores the players current item(currently just key - bomb and others in future)
	Riddle - stores each question and its answer
	GameUtils - holds common expressions and basic functions used globably
	

	
	
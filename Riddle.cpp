#include "Riddle.h"

const Riddle RIDDLES_LEVEL1[] = {
	Riddle(
		"Why did the computer go to the doctor?",
		"It needed more RAM",
		"It had a virus",
		"It crashed too often",
		"It forgot its password",
		1
	)
};
const int NUM_RIDDLES_LEVEL1 = sizeof(RIDDLES_LEVEL1) / sizeof(Riddle);

const Riddle RIDDLES_LEVEL2[] = {
	Riddle(
		"What is the binary representation of the number 5?",
		"101",
		"011",
		"111",
		"001",
		0
	),
	Riddle(
		"What Does CPU stand for?",
		"Central Power Unit",
		"Computer Power Unit",
		"Central Processing Unit",
		"None of the above",
		2
	)
};
const int NUM_RIDDLES_LEVEL2 = sizeof(RIDDLES_LEVEL2) / sizeof(Riddle);


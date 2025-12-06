#include "Riddle.h"

const Riddle RIDDLES_LEVEL1[] = {
	Riddle(
		"What has keys but can't open locks?",
		"A Piano",
		"A Map",
		"A Clock",
		"A River",
		0
	),
};

const int NUM_RIDDLES_LEVEL1 = sizeof(RIDDLES_LEVEL1) / sizeof(Riddle);

const Riddle RIDDLES_LEVEL2[] = {
	Riddle(
		"What has to be broken before you can use it?",
		"A Mirror",
		"An Egg",
		"A Seal",
		"A Code",
		1
	),
};

const int NUM_RIDDLES_LEVEL2 = sizeof(RIDDLES_LEVEL2) / sizeof(Riddle);

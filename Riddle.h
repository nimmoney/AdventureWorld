#pragma once

class Riddle
{
private: 
	const char* question;
	const char* answers[4];
	int correctAnswer; // index 0-3
public:
	Riddle(const char* q, const char* a1, const char* a2, const char* a3, const char* a4, int correct)
		: question(q), correctAnswer(correct)
	{
		answers[0] = a1;
		answers[1] = a2;
		answers[2] = a3;
		answers[3] = a4;
	}
	const char* getQuestion() const { return question; }
	const char* getAnswer(int index) const { return answers[index]; }
	int getCorrectAnswer() const { return correctAnswer; }
};

extern const Riddle RIDDLES_LEVEL1[];
extern const int NUM_RIDDLES_LEVEL1;
extern const Riddle RIDDLES_LEVEL2[];
extern const int NUM_RIDDLES_LEVEL2;

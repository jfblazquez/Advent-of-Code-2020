#include "Day15.h"
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

Day15::Day15()
{
	cout << endl << "DAY 15" << endl;
}

void Day15::Puzzle1()
{
	unordered_map<int, int> numbers = { {6,1}, {19,2}, {0,3}, {5,4}, {7,5}, {13,6} };
	// Last turn and number are not in map yet
	int lastNumber = 1;
	int turn = 8;

	const int turnTarget = 2020;
	while (turn <= turnTarget)
	{
		int answer = 0;
		if (numbers.find(lastNumber) != numbers.end())
		{
			answer = (turn - 1) - numbers[lastNumber];
		}
		numbers[lastNumber] = turn - 1;
		lastNumber = answer;
		turn++;
	}

	cout << "Puzzle 1 answer: " << lastNumber << endl;
}

void Day15::Puzzle2()
{
	unordered_map<int, int> numbers = { {6,1}, {19,2}, {0,3}, {5,4}, {7,5}, {13,6} };
	// Last turn and number are not in map yet
	int lastNumber = 1;
	int turn = 8;

	const int turnTarget = 30000000; // Brute force. but it works in an reasonable amount of time
	while (turn <= turnTarget)
	{
		int answer = 0;
		if (numbers.find(lastNumber) != numbers.end())
		{
			answer = (turn - 1) - numbers[lastNumber];
		}
		numbers[lastNumber] = turn - 1;
		lastNumber = answer;
		turn++;
	}

	cout << "Puzzle 2 answer: " << lastNumber << endl;
}
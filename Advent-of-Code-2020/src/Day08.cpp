#include "Day08.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>

using namespace std;

Day08::Day08() : mInputFile{ "inputs/day08.txt" }
{
	cout << endl << "DAY 08" << endl;
    ReadData();
}

void Day08::Puzzle1()
{
	ExecuteProgram();
	cout << "Puzzle 1 answer: " << mAccumulator << endl;
}

void Day08::Puzzle2()
{
	// Brute force approach.
	// Swap one instruction and try the code.
	// If success, the code is correct.
	// If not, restore the instruction and swap the next one
	for (int i = 0; i < mIns.size(); ++i)
	{
		if (SwapInstruction(i))
		{
			if (ExecuteProgram()) break;
			SwapInstruction(i);
		}
	}

	cout << "Puzzle 2 answer: " << mAccumulator << endl;
}

bool Day08::ExecuteProgram()
{
	ResetInstructions();
	mAccumulator = 0;

	int opIdx = 0;
	while (opIdx < mIns.size())
	{
		auto& ins = mIns[opIdx];

		if (ins.executed) return false;
		else ins.executed = true;

		if (ins.op == "nop")
		{
			++opIdx;
		}
		else if (ins.op == "acc")
		{
			mAccumulator += ins.value;
			++opIdx;
		}
		else if (ins.op == "jmp")
		{
			opIdx += ins.value;
		}

	}

	return true;
}

void Day08::ResetInstructions()
{
	for (auto& ins : mIns)
	{
		ins.executed = false;
	}
}

bool Day08::SwapInstruction(int i)
{
	if (mIns[i].op == "acc") return false;
	else if (mIns[i].op == "jmp") mIns[i].op = "nop";
	else if (mIns[i].op == "nop") mIns[i].op = "jmp";
	return true;
}

void Day08::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	regex r{ "([a-z]{3}) ([\\-\\+][0-9]+)" };
	smatch m;
	for (string line; getline(ifs, line); )
	{
		regex_search(line, m, r);
		string op = m[1];
		int v = stoi(m[2]);

		mIns.push_back(Instruction(op, v));
	}
}
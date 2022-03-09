#pragma once
#include <string>
#include <vector>

struct Instruction
{
	Instruction(std::string o, int v) : op{o}, value{v} {}

	std::string op;
	int value;
	bool executed{ false };
};

class Day08
{
public:
	Day08();

	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();
	
	// Execute the program and returns TRUE if success or FALSE if infinite loop
	bool ExecuteProgram();
	
	// Put all instructions to 'not executed' state
	void ResetInstructions();
	
	// Convert instruction 'i' from 'jmp' to 'nop' and vice versa
	// If instruction is 'acc', do nothing and returns FALSE
	bool SwapInstruction(int i);

	std::string mInputFile;
	std::vector<Instruction> mIns;
	int mAccumulator;
};


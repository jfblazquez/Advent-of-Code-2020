#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <utility>

struct InstructionSet
{
	InstructionSet(std::string m) : mask {m} {}

	std::string mask;
	std::vector<std::pair<int, long long>> moves;
};

class Day14
{
public:
	Day14();
	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();
	void ExecProgram1();
	void ExecProgram2();

	std::string mInputFile;

	std::vector<std::unique_ptr<InstructionSet>> mInstructions;
	std::map<long long, long long> mMemory;
};
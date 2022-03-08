#pragma once
#include <string>
#include <unordered_map>
#include <utility>

struct Bag
{
	Bag(std::string n) : name{n} {}
	std::string name;
};

class Day07
{
public:
	Day07();
	~Day07();
	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();
	int BagsInside(Bag* b);

	//std::unordered_map<std::string, int> mBagNameToId;
	//std::unordered_map<int, std::string> mBagIdToName;
	std::unordered_map<std::string, Bag*> mBags;
	std::unordered_map<Bag*, std::vector<Bag*>> mContentGraph;
	std::unordered_map<Bag*, std::vector<std::pair<Bag*, int>>> mContainerGraph;

	std::string mInputFile;
};
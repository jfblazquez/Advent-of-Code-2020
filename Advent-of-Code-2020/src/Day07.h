#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <memory>
#include <iostream>
#include <vector>

struct Bag
{
	Bag(std::string n) : name{n} {}
	std::string name;
};

class Day07
{
public:
	Day07();
	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();
	int BagsInside(const std::shared_ptr<Bag>& b);

	//std::unordered_map<std::string, int> mBagNameToId;
	//std::unordered_map<int, std::string> mBagIdToName;
	std::unordered_map<std::string, std::shared_ptr<Bag>> mBags;
	std::unordered_map<std::shared_ptr<Bag>, std::vector<std::shared_ptr<Bag>>> mContentGraph;
	std::unordered_map<std::shared_ptr<Bag>, std::vector<std::pair<std::shared_ptr<Bag>, int>>> mContainerGraph;

	std::string mInputFile;
};
#include "Day07.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

const string TARGET_BAG = "shiny gold";

Day07::Day07() : mInputFile{ "inputs/day07.txt" }
{
	cout << endl << "DAY 07" << endl;
    ReadData();
}

Day07::~Day07()
{
	mContentGraph.clear();
	mContainerGraph.clear();
	for (const auto& b : mBags)
	{
		delete b.second;
	}
	mBags.clear();
}

void Day07::Puzzle1()
{
	stack<Bag*> stack;
	stack.push(mBags[TARGET_BAG]);
	set<Bag*> visitedBags;

	while (!stack.empty())
	{
		Bag* current = stack.top();
		stack.pop();

		if (visitedBags.count(current) == 0)
		{
			visitedBags.insert(current);
			for (const auto p : mContentGraph[current])
			{
				stack.push(p);
			}
		}
	}

	int c = std::count_if(visitedBags.begin(), visitedBags.end(), [](Bag* b) {return b->name != TARGET_BAG; });

	cout << "Puzzle 1 answer: " << c << endl;
}

void Day07::Puzzle2()
{
	int c = BagsInside(mBags[TARGET_BAG]);
	cout << "Puzzle 2 answer: " << c << endl;
}

int Day07::BagsInside(Bag* b)
{
	int c = 0;

	for (const auto& p : mContainerGraph[b])
	{
		c += p.second + p.second * BagsInside(p.first);
	}

	return c;
}

void Day07::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	int id = 0;

	regex regex_container{ "([a-z]+ [a-z]+) (bags)" };
	smatch matches;
	for (string line; getline(ifs, line);)
	{
		regex_search(line, matches, regex_container);
		string container{ matches[1]};

		regex regex_contents{ "([0-9]+) ([a-z]+ [a-z]+) (bag[s]?)" };
		vector<pair<int, string>> contents;
		while (regex_search(line, matches, regex_contents))
		{
			contents.push_back(make_pair(stoi(matches[1]), matches[2]));
			line = matches.suffix();
		}

		// Add container bag
		if (!mBags.count(container))
		{
			mBags.insert(make_pair(container, new Bag(container)));
		}
		Bag* bagContainer = mBags[container];
		mContainerGraph.insert(make_pair(bagContainer, vector<pair<Bag*, int>>()));

		// Add content bags
		for (const auto& b : contents)
		{
			if (!mBags.count(b.second))
			{
				mBags.insert(make_pair(b.second, new Bag(b.second)));
			}
			Bag* bagContent = mBags[b.second];

			if (!mContentGraph.count(bagContent))
			{
				mContentGraph.insert(make_pair(bagContent, vector<Bag*>()));
			}

			mContentGraph[bagContent].push_back(bagContainer);
			mContainerGraph[bagContainer].push_back(make_pair(bagContent, b.first));
		}
	}
}

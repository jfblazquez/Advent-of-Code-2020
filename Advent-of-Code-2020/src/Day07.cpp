#include "Day07.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

const string TARGET_BAG = "shiny gold";

Day07::Day07() : mInputFile{ "inputs/Day07.txt" }
{
	cout << endl << "DAY 07" << endl;
    ReadData();
}

void Day07::Puzzle1()
{
	stack<shared_ptr<Bag>> stack;
	stack.push(mBags[TARGET_BAG]);
	set<shared_ptr<Bag>> visitedBags;

	while (!stack.empty())
	{
		shared_ptr<Bag> current = stack.top();
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

	int c = std::count_if(visitedBags.begin(), visitedBags.end(), [](const shared_ptr<Bag>& b) {return b->name != TARGET_BAG; });

	cout << "Puzzle 1 answer: " << c << endl;
}

void Day07::Puzzle2()
{
	int c = BagsInside(mBags[TARGET_BAG]);
	cout << "Puzzle 2 answer: " << c << endl;
}

int Day07::BagsInside(const shared_ptr<Bag>& b)
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

	regex regex_container{ "([a-z ]+) bags" };
	regex regex_contents{ "([0-9]+) ([a-z ]+) bags?" };
	smatch matches;
	for (string line; getline(ifs, line);)
	{
		regex_search(line, matches, regex_container);
		string container{ matches[1]};
		line = matches.suffix();
		
		vector<pair<int, string>> contents;
		while (regex_search(line, matches, regex_contents))
		{
			contents.push_back(make_pair(stoi(matches[1]), matches[2]));
			line = matches.suffix();
		}

		// Add container bag
		if (!mBags.count(container))
		{
			mBags.insert(make_pair(container, make_shared<Bag>(container)));
		}
		std::shared_ptr<Bag> bagContainer = mBags[container];
		mContainerGraph.insert(make_pair(bagContainer, vector<pair<std::shared_ptr<Bag>, int>>()));

		// Add content bags
		for (const auto& b : contents)
		{
			if (!mBags.count(b.second))
			{
				mBags.insert(make_pair(b.second, new Bag(b.second)));
			}
			std::shared_ptr<Bag> bagContent = mBags[b.second];

			if (!mContentGraph.count(bagContent))
			{
				mContentGraph.insert(make_pair(bagContent, vector<std::shared_ptr<Bag>>()));
			}

			mContentGraph[bagContent].push_back(bagContainer);
			mContainerGraph[bagContainer].push_back(make_pair(bagContent, b.first));
		}
	}
}

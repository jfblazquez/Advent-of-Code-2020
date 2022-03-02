#include "Day01.h"
#include <iostream>
#include <fstream>

using namespace std;

Day01::Day01() : mInputFile{"inputs/day01.txt"}
{
    cout << endl << "DAY 01" << endl;
    ReadData();
}

void Day01::Puzzle1()
{
    unordered_set<int> numbers;
    for (auto d : mData)
    {
        if (numbers.find(mTarget - d) != numbers.end())
        {
            cout << "Puzzle 1 answer: " << (mTarget - d) * d << endl;
        }
        else
        {
            numbers.insert(d);
        }
    }
}

void Day01::Puzzle2()
{
    for (size_t i = 0; i < mData.size(); ++i)
    {
        auto d1 = mData[i];
        unordered_set<int> numbers;
        int localTarget = mTarget - d1;
        for (size_t j = i + 1; j < mData.size(); ++j)
        {
            auto d2 = mData[j];
            if (numbers.find(localTarget - d2) != numbers.end())
            {
                cout << "Puzzle 2 answer: " << d1 * d2 * (localTarget - d2) << endl;
            }
            else
            {
                numbers.insert(d2);
            }
        }
    }
}

void Day01::ReadData()
{
    ifstream ifs(mInputFile, ios::binary);
    while (!ifs.eof()) {
        int d;
        ifs >> d;
        mData.push_back(d);
    }
}

#include "Day14.h"
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <cmath>

using namespace std;

Day14::Day14() : mInputFile{ "inputs/day14.txt" }
{
	cout << endl << "DAY 14" << endl;
    ReadData();
}

void Day14::Puzzle1()
{	
	ExecProgram1();

	const long long result = std::accumulate(std::begin(mMemory), std::end(mMemory), 0ll,
		[](const long long previous, const std::pair<long long, long long>& p)
		{ return previous + p.second; });

	cout << "Puzzle 1 answer: " << result << endl;
}

void Day14::Puzzle2()
{
	ExecProgram2();

	const long long result = std::accumulate(std::begin(mMemory), std::end(mMemory), 0ll,
		[](const long long previous, const std::pair<long long, long long>& p)
		{ return previous + p.second; });

	cout << "Puzzle 2 answer: " << result << endl;
}

void Day14::ExecProgram1()
{
	mMemory.clear();

	for (const auto& ins : mInstructions)
	{
		string mask0{ ins->mask };
		string mask1{ ins->mask };
		std::replace(mask0.begin(), mask0.end(), 'X', '0');
		std::replace(mask1.begin(), mask1.end(), 'X', '1');

		for (const auto& m : ins->moves)
		{
			int address = m.first;
			long long value = m.second;
			value |= stoll(mask0, nullptr, 2);
			value &= stoll(mask1, nullptr, 2);
			mMemory[address] = value;
		}		
	}
}

void Day14::ExecProgram2()
{
	mMemory.clear();

	for (const auto& ins : mInstructions)
	{
		string mask = ins->mask;
		for (const auto& m : ins->moves)
		{
			unsigned long long address = m.first;
			long long value = m.second;

			string floatingAddress = bitset<36>(address).to_string();
			for (int i = 0; i < mask.size(); ++i)
			{
				if (mask[i] != '0')
				{
					floatingAddress[i] = mask[i];
				}
			}

			auto xs = count(floatingAddress.begin(), floatingAddress.end(), 'X');

			// Go throught all possibilities and replace 'X' with the correct bit
			for (int i = 0; i < std::pow(2, xs); ++i)
			{
				string newAddress{ floatingAddress };
				int j = static_cast<int>(pow(2, xs-1)); // Most significant bit
				while (j > 0)
				{
					auto pos = find(newAddress.begin(), newAddress.end(), 'X');
					*pos = (i & j) >= 1 ? '1' : '0';
					j = j >> 1;
				}

				mMemory[stoll(newAddress, nullptr, 2)] = value;
			}
		}
	}
}

void Day14::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	regex rMask{ "mask = ([01X]+)" };
	regex rValue{ "mem\\[([0-9]+)\\] = ([0-9]+)" };
	smatch m;
	for (string line;getline(ifs, line);)
	{
		if (regex_match(line, m, rMask))
		{
			mInstructions.emplace_back(make_unique<InstructionSet>(m[1].str()));
		}
		else if(regex_match(line, m, rValue))
		{
			mInstructions.back()->moves.push_back(make_pair(stoi(m[1]), stoll(m[2])));
		}
	}
}
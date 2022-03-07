#include "Day04.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

vector<string> validKeys{ "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };

Day04::Day04() : mInputFile{ "inputs/day04.txt" }
{
	cout << endl << "DAY 04" << endl;
    ReadData();
}

void Day04::Puzzle1()
{
	cout << "Puzzle 1 answer: " << std::count_if(mPassports.begin(), mPassports.end(), [](const unique_ptr<Passport>& p){ return p->IsValid(false); }) << endl;
}

void Day04::Puzzle2()
{
	cout << "Puzzle 2 answer: " << std::count_if(mPassports.begin(), mPassports.end(), [](const unique_ptr<Passport>& p) { return p->IsValid(true); }) << endl;
}

void Day04::ReadData()
{
	std::ifstream ifs(mInputFile);
	if (ifs.fail())
	{
		return;
	}

	mPassports.emplace_back(make_unique<Passport>());
	string line;
	while (getline(ifs, line))
	{
		if (line.empty())
		{
			mPassports.emplace_back(make_unique<Passport>());
		}
		else
		{
			regex pf{ "([a-z]{3}):([a-zA-Z0-9#]+)" };
			smatch m;
			while (regex_search(line, m, pf))
			{
				string key = m[1].str();
				string value = m[2].str();
				mPassports.back()->AddField(key, value);
				line = m.suffix();
			}
		}
	}
}

bool Passport::AddField(string key, string value)
{
	if (std::find(validKeys.begin(), validKeys.end(), key) != validKeys.end())
	{
		if (!mFields.count(key))
		{
			mFields.insert({ key, value });
			return true;
		}
	}

	return false;
}

bool Passport::IsValid(bool validateFields)
{
	if (mFields.size() == 8 ||
		(mFields.size() == 7 && mFields.count("cid") == 0))
	{
		return !validateFields || BirthYearValid() &&
			IssueYearValid() &&
			ExpirationYearValid() &&
			HeightValid() &&
			HairColorValid() &&
			EyeColorValid() &&
			IdValid();
	}
	return false;
}

bool Passport::BirthYearValid()
{
	regex pf{ "[0-9]{4}" };
	smatch m;
	if (regex_match(mFields["byr"], m, pf))
	{ 
		auto year = stoi(m[0]);
		return 1920 <= year && year <= 2002;
	}
	return false;
}

bool Passport::IssueYearValid()
{
	regex pf{ "[0-9]{4}" };
	smatch m;
	if (regex_match(mFields["iyr"], m, pf))
	{
		auto year = stoi(m[0]);
		return 2010 <= year && year <= 2020;
	}
	return false;
}

bool Passport::ExpirationYearValid()
{
	regex pf{ "[0-9]{4}" };
	smatch m;
	if (regex_match(mFields["eyr"], m, pf))
	{
		auto year = stoi(m[0]);
		return 2020 <= year && year <= 2030;
	}
	return false;
}

bool Passport::HeightValid()
{
	regex pf{ "([0-9]+)(cm|in)" };
	smatch m;
	if (regex_match(mFields["hgt"], m, pf))
	{
		int h = stoi(m[1]);
		string s = m[2];
		if (s == "cm")
		{
			return 150 <= h && h <= 193;
		}
		else if (s == "in")
		{
			return 59 <= h && h <= 76;
		}
	}
	return false;
}

bool Passport::HairColorValid()
{
	regex pf{ "#[a-f0-9]{6}" };
	smatch m;
	return regex_match(mFields["hcl"], m, pf);
}

bool Passport::EyeColorValid()
{
	string ec = mFields["ecl"];
	return ec == "amb" || ec == "blu" || ec == "brn" || ec == "gry" || ec == "grn" || ec == "hzl" || ec == "oth";
}

bool Passport::IdValid()
{
	regex pf{ "[0-9]{9}" };
	smatch m;
	return regex_match(mFields["pid"], m, pf);
}

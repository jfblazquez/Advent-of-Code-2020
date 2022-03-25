#include "Day02.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;


Day02::Day02() : mInputFile{ "inputs/Day02.txt" }
{
    cout << endl << "DAY 02" << endl;
}

void Day02::Puzzle1()
{
    ifstream ifs{ mInputFile };

    std::regex regex{ "([0-9]+)-([0-9]+) ([a-zA-Z]{1}): (.+)" };
    std::smatch matches;

    auto validPasswords{ 0 };
    for (std::string p; std::getline(ifs, p);)
    {
        if (std::regex_search(p, matches, regex))
        {
            int low = std::stoi(matches[1].str());
            int high = std::stoi(matches[2].str());
            char token = matches[3].str()[0];
            std::string password = matches[4].str();

            auto times = std::count(password.cbegin(), password.cend(), token);
            if (low <= times && times <= high)
            {
                ++validPasswords;
            }
        }
    }

    cout << "Puzzle 1 answer: " << validPasswords << endl;
}

void Day02::Puzzle2()
{
    ifstream ifs{ mInputFile };

    std::regex regex{ "([0-9]+)-([0-9]+) ([a-zA-Z]{1}): (.+)" };
    std::smatch matches;

    auto validPasswords{ 0 };
    for (std::string p; std::getline(ifs, p);)
    {
        if (std::regex_search(p, matches, regex))
        {
            int low = std::stoi(matches[1].str());
            int high = std::stoi(matches[2].str());
            char token = matches[3].str()[0];
            std::string password = matches[4].str();

            if((password[low - 1] == token) ^ (password[high - 1] == token))
            {
                ++validPasswords;
            }
        }
    }

    cout << "Puzzle 2 answer: " << validPasswords << endl;
}

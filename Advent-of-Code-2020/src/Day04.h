#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class Passport
{
public:
	bool AddField(std::string key, std::string value);

	bool IsValid(bool validateFields);

private:
	bool BirthYearValid();
	bool IssueYearValid();
	bool ExpirationYearValid();
	bool HeightValid();
	bool HairColorValid();
	bool EyeColorValid();
	bool IdValid();

	std::unordered_map<std::string, std::string> mFields;
};

class Day04
{
public:
	Day04();

	void Puzzle1();
	void Puzzle2();

private:

	void ReadData();

	std::string mInputFile;
	std::vector<std::shared_ptr<Passport>> mPassports;
};


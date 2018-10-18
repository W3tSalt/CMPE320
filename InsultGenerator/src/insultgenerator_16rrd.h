
#pragma once

#include <string>
#include <vector>
using namespace std;

class FileException {
public:
	FileException(const string& message);
	string& what();

private:
	string message;
};

class NumInsultsOutOfBounds {
public:
	NumInsultsOutOfBounds(const string& message);
	string& what();

private:
	string message;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class InsultGenerator {
public:
	void initialize();												// Gets source phrases from InsultSouce.txt
	string talkToMe();												// Return single randomly generated insult
	vector<string> generate(const int& num);						// Generates given number of unique insults
	vector<string> sort(const vector<string>& list);				// Given list of strings sort them alphabetically and return new list
	void generateAndSave(const string& fileName, const int& num);	// Generates number of insults and saves to given file name in alphabetical order

private:
	vector<string> attribute1;
	vector<string> attribute2;
	vector<string> attribute3;
};

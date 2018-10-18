#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

#include "insultgenerator_16rrd.h"

using namespace std;

FileException::FileException(const string& message) : message(message) {}
string& FileException::what() { return message; }

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message) : message(message) {}
string& NumInsultsOutOfBounds::what() { return message; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InsultGenerator::initialize() {
	string tempString;

	ifstream fileIn("InsultSource.txt");
	if(fileIn.fail()) {
		throw FileException("ERROR: Failed to open insult source file");
	}
	for(int i = 0; i < 50; i++) {
		getline(fileIn, tempString);
		attribute1.push_back((tempString.substr(0, tempString.find("	"))));
		attribute2.push_back(tempString.substr(tempString.find("	")+1, tempString.rfind("	")-tempString.find("	")-1));
		attribute3.push_back(tempString.substr(tempString.rfind("	")+1, (int)(tempString.size())-tempString.rfind("	")));
	}
	fileIn.close();
}

string InsultGenerator::talkToMe() {
	string insult;
	srand(time(NULL));

	insult = "Thou " + attribute1[rand()%50] + ' ' + attribute2[rand()%50] + ' ' + attribute3[rand()%50] + '!';

	return insult;
}

vector<string> InsultGenerator::generate(const int& num) {
	vector<string> list;
	vector<int> madeInsults;
	srand(time(NULL));

	if(num <= 0) {
		throw NumInsultsOutOfBounds("ERROR: Number trying to generate is less than or equal to 0");
	} else if (num > 10000) {
		throw NumInsultsOutOfBounds("ERROR: Number trying to generate is larger than 10 000");
	} else{
		string tempInsult;
		int att1, att2, att3;

		att1 = rand()%50;
		att2 = rand()%50;
		att3 = rand()%50;
		tempInsult = "Thou " + attribute1[att1] + ' ' + attribute2[att2] + ' ' + attribute3[att3] + '!';
		list.push_back(tempInsult);
		madeInsults.push_back(att1*10000 + att2*100 + att3);

		for(int i = 2; i <= num; i++) {
			att1 = rand()%50;
			att2 = rand()%50;
			att3 = rand()%50;

			while(find(madeInsults.begin(), madeInsults.end(), att1*10000 + att2*100 + att3) != madeInsults.end()) {
				att1 = rand()%50;
				att2 = rand()%50;
				att3 = rand()%50;
			}
			tempInsult = "Thou " + attribute1[att1] + ' ' + attribute2[att2] + ' ' + attribute3[att3] + '!';
			list.push_back(tempInsult);
			madeInsults.push_back(att1*10000 + att2*100 + att3);
		}
		return list;
	}
	return list;
}

void InsultGenerator::generateAndSave(const string& saveName, const int& num) {
	vector<string> listToFile;

	listToFile = generate(num);
	std::sort(listToFile.begin(), listToFile.end());

	//print to file
	ofstream insultFile(saveName);
	if(insultFile.is_open()){
		for(int i = 0; i < (int)(listToFile.size()); i++){
			insultFile << listToFile[i] << endl;
		}
	} else{
		throw FileException("ERROR: Could not open file to save too");
	}


}

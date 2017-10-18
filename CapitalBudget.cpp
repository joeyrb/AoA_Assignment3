#include "CapitalBudget.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


CapitalBudget::CapitalBudget()
{

}

// Initialize object from a file
CapitalBudget::CapitalBudget(fstream &file)
{

}

CapitalBudget::~CapitalBudget()
{

}

// Safely open a file
bool CapitalBudget::openFileIn(fstream &file, string name)
{
	file.open(name.c_str(), ios::in);
	if (file.fail())
		return false;
	else
		return true;
}

// Return a vector of nums from a string
vector<int> CapitalBudget::getNums(string str)
{
	// Find space separating integers
	vector<int> nums;
	stringstream ss;
	ss << str;
	string temp;
	int found;
	if(str.size() > 0)
	{
		while(!ss.eof())
		{
			// extract characters from string
			ss >> temp;
			// check if int
			if(stringstream(temp) >> found)
			{
				nums.push_back(found);
			}
			temp = "";
		}
	}
	return nums;
}

// Display the contents of a file
void CapitalBudget::displayFile(fstream &file)
{
	string line;		// Stores text read from txt file
	vector<int> nums;	// Stores ints read from txt file

	cout << "\nContents: \n";
	cout <<   "------------------------\n";
	
	while(!file.eof())
	{
		getline(file, line, '\n');
		
		nums = getNums(line);

		// Quit processing if reading the end of file
		if(file.eof())
			break;

		// Display contents of text file 
		if(nums.size() > 0)
		{
			for (int i = 0; i < nums.size(); ++i)
			{
				cout << nums.at(i) << " ";
			}
			cout << endl;
		}
	}
	cout <<   "------------------------\n";
}

// Read a file
void CapitalBudget::readFile(const char* infile)
{
	fstream file;
	if(openFileIn(file, infile))
	{
		cout << endl << infile << " opened successfully.\n";
		displayFile(file);
		file.close();
	}
	else 
		cout << "File open error" << endl;
	cout << "\nFile closed\n";
}

// // Overloaded readFile with string
// void CapitalBudget::readFile(string infile)
// {

// }

// // Overloaded readFile with fstream
// void CapitalBudget::readFile(fstream &infile)
// {

// }
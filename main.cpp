/************************************************************************
Program:		Assignment 3
Author:			Joey Brown
Class:			CSC372 Analysis of Algorithms
Instructor:		Dr. Rebenitsch
Date:			October 24, 2017
Description:	
*************************************************************************/
#include "CapitalBudget.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

struct Proposal
{
	int numLocations;
	vector<int> numProp;	// Number of proposals per location
	vector<int> cost;
	vector<int> revenue;

	void setProps(string str)
	{
		// Find space separating integers
		vector<int> nums;
		stringstream ss;
		ss << str;
		string temp;
		int found;
		while(!ss.eof())
		{
			// extract characters from string
			ss >> temp;
			// check if int
			if(stringstream(temp) >> found)
			{
				// cout << found << " ";
				nums.push_back(found);
			}
			temp = "";
		}
		cout << "Size: " << nums.size() << endl;
		cout << nums[0] << " " << nums[1] << endl;
	}

};

// Check if the line read is number of locations
bool isLocation(string s)
{
	if (s.size() <= 2)
		return true;
	else
		return false;
}

// Check if line read is number of proposals for a location
bool isProposal(string s, bool locFound)
{
	if (locFound && s.size() <= 2)
		return true;
	else
		return false;
}

// Check for errors while opening the file
bool openFileIn(fstream &file, string name)
{
	file.open(name.c_str(), ios::in);
	if (file.fail())
		return false;
	else
		return true;
}

// Get vector of integers from a string
vector<int> getNums(string str)
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

// Display the file from the input
void displayFile(fstream &file)
{		
	string line;		// Stores text read from txt file
	vector<int> nums;	// Stores ints read from txt file

	cout << "\nDisplaying Contents: \n";
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
}



// KEEP THIS FUNCTION????
// Saves the contents of the file to a structure
Proposal extract(fstream &file)
{
	Proposal p;
	bool locationsFound = false;
	string line;
	while(!file.eof())
	{
		getline(file,line);
		if (isLocation(line) && !file.eof() && locationsFound == false)
		{
			p.numLocations = stoi(line);
			locationsFound = true;
			getline(file,line);
			
		}
		if (isProposal(line, locationsFound) && !file.eof())
		{
			p.numProp.push_back( stoi(line) );
		}
	}

	return p;
}

// Accept the starting amount and proposals cost and
//	revenue from a file via command line.
void readInput(const char* infile)
{
	// Read input as:
	// 	Num_locations
	// 	num_proposals_for_location_1
	// 	Proposal_1.1_cost Proposal_1.1_revenue
	// 	Proposal_1.2_cost Proposal_1.2_revenue
	// 	...
	// 	Num_proposals_for_location_2
	// 	Proposal_2.1_cost Proposal_2.1_revenue
	// 	Proposal_2.2_cost Proposal_2.2_revenue
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





/*
// Max starting value = 15
// Input = integer
// Print state of algorithm at several locations:
//		- Proposals and costs per location after reading it in (tables)
//		- The current revenues, and "split" value(s) for each
//				starting amount after completing each location (tables)
//		- The final revenue and the plans selected at each location.
//		- Output the run time for the naive test and the dynamic test.
//			The purpose of this is to show that you used dynamic 
//			storage properly.
// Use < or > when updating (not >= or <=, since that will give different results)

// 5 points for implementing your split structure.
// 5 points for using split structure correctly

// 5 points for correct output at 1 location
// 5 points for correct output at 2 locations
// 5 points for correct output at 3 locations
// 5 points for correct output at n locations
// 0 POINTS FOR NOT PASSING ANY TESTS

// 10 for using dynamic storage correctly (all or nothing)

// Do NOT USE system("Pause"), cin>>var, etc to see the output in MSVS.
// Put anything that is not working in the header for partial credit.
*/

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		printf("Usage: %s file_name start_amount\n", argv[0]);
	}
	

	int last = argc - 1; 	// Index to the last element of the command line args

	// Convert const char* to int
	stringstream ss;
	ss << argv[last];
	
	int start_amount;
	ss >> start_amount;

	CapitalBudget cb;
	cout << "Start amout: " << start_amount << endl;


	// Read all files from input
	for (int i = 1; i < argc-1; ++i)
	{
		// readInput(argv[i]);
		cb.readFile(argv[i]);
	}

	return 0;
}

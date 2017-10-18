/************************************************************************
Program:		Assignment 3
Author:			Joey Brown
Class:			CSC372 Analysis of Algorithms
Instructor:		Dr. Rebenitsch
Date:			October 24, 2017
Description:	
*************************************************************************/
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
		// size_t found = str.find(" ");
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
				cout << found << " ";
			}
			temp = "";
			cout << endl;
		}
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

// Display the file from the input
void displayFile(fstream &file)
{
	bool locationsFound = false;
	Proposal p;
	char ch;
	string line;
	cout << "\nDisplaying Contents: \n";
	cout <<   "------------------------\n";
	// while(!file.eof())
	// {
	// 	getline(file,line);

	// 	if (isLocation(line) && !file.eof() && locationsFound == false)
	// 	{
	// 		cout << "Number locations: " << line << endl;
	// 		p.numLocations = stoi(line);
	// 		locationsFound = true;
	// 	}
	// 	else if (isProposal(line, locationsFound) && !file.eof())
	// 	{
	// 		cout << "Number proposals: " << line << endl;
	// 		p.numProposals.push_back( stoi(line) );
	// 	}
	// 	file.get(ch);
	// 	while(ch != '\n')
	// 	{
	// 		if(ch != ' ' || ch != '\n')
	// 			cout << '*' << ch << endl;
	// 		file.get(ch);
	// 	}
	// }
	// Read characters character by character
	// getline(file,line);
	// cout << "line: " << line << endl;
	
	file.get(ch);
	cout << "Locations: " << ch << endl;
	p.numLocations = (int)ch;
	locationsFound = true;
	while(!file.eof())
	{
		getline(file, line, '\n');
		// cout << "\nlen: " << line.length() << endl;
		// cout << "size: " << line.size() << endl;

		if(line.size() <= 2)
			cout << "" << endl;
		else
		{
			p.setProps(line);
			// cout << line << endl;
		}
	}
}




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
		cout << "File opened successfully.\n";
		displayFile(file);
		file.close();
		cout << "\nend of file\n";
	}
	else 
		cout << "File open error" << endl;
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
	readInput(argv[1]);

	return 0;
}

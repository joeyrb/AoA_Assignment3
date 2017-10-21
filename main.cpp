/************************************************************************
Program:		Assignment 3
Author:			Joey Brown
Class:			CSC372 Analysis of Algorithms
Instructor:		Dr. Rebenitsch
Date:			October 24, 2017
Description:	
	Max starting value = 15
	Input = integer
	Print state of algorithm at several locations:
			- Proposals and costs per location after reading it in (tables)
			- The current revenues, and "split" value(s) for each
					starting amount after completing each location (tables)
			- The final revenue and the plans selected at each location.
			- Output the run time for the naive test and the dynamic test.
				The purpose of this is to show that you used dynamic 
				storage properly.
	Use < or > when updating (not >= or <=, since that will give different results)

	5 points for implementing your split structure.
	5 points for using split structure correctly

	5 points for correct output at 1 location
	5 points for correct output at 2 locations
	5 points for correct output at 3 locations
	5 points for correct output at n locations
	0 POINTS FOR NOT PASSING ANY TESTS

	10 for using dynamic storage correctly (all or nothing)

	Do NOT USE system("Pause"), cin>>var, etc to see the output in MSVS.
	Put anything that is not working in the header for partial credit.
*************************************************************************/
#include "CapitalBudget.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;


/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/
// Check for errors while opening the file
bool openFileIn(fstream &file, string name)
{
	file.open(name.c_str(), ios::in);
	if (file.fail())
		return false;
	else
		return true;
}

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/
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

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/
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


/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/
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




// Permutations
void PermuteSet(CapitalBudget S, int location, int size, vector<int> p)
{
	int n = S.getNumProposalsAt(location);
	if(size >= n)
	{
		int sum = 0;
		for (int i = 0; i < n; ++i)
		{
			sum += p.at(i);
			cout << p.at(i) << " ";
		}
		// cout << " * ";
		// cout << sum << " " ;
		// cout << endl;
		return;
	}
	for(int j = 0; j < (n-size); ++j)
	{
		p.at(size) = (S.getRevenueAt(location,j));
		PermuteSet(S, location, size+1, p);
	}
}

// TODO: 
//		- Apply the permute set function to iterate through number of locations
void PermuteRec(int n, int size, vector<int> p, bool* used)
{
	if(size >= n)
	{
		for(int i = 0; i < n; ++i)
		{
			cout << p.at(i) << " ";
		}
		cout << endl;
		return;
	}
	// For each location, find permutations of each set
	for (int i = 0; i < n; ++i)
	{
		if( !used[i] )
		{
			p.at(size) = i;
			used[i] = true;
			PermuteRec(n, size+1, p, used);
			used[i] = false;
		}
	}
}

// Dynamic approach
void dynamicApproach()
{
	// check for each proposal we can afford and keep the max
	// last location = BASE CASE
}



/************************************************************************/
/*****************************MAIN***************************************/
/************************************************************************/

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
	
	// Set the starting amount to the last argument from command line input
	CapitalBudget cb(argv[1]);
	int amnt;
	ss >> amnt;
	cb.setStartAmount(amnt);
	cb.setAvailableAmount(cb.getStartAmount());

	// PRINT STATES AT VARIOUS POINTS 

	// PRINT STATE: proposals and costs per location after reading from input
	cb.printContents();


	// Naive approach
	vector<int> p;
	p.resize(5040);
	// PermuteSet(cb, 0, 0, p);
	
	for (int j = 0; j < cb.getNumLocations(); ++j)
	{
		vector<int> q;
		q.resize(6000);
		bool* used = new bool[cb.getNumProposalsAt(j)];
		for (int i = 0; i < sizeof(used); ++i)
		{
			used[i] = false;
		}
		PermuteRec(cb.getNumProposalsAt(j), 0, q, used);
		cout << endl;
		q.resize(0);
	}




	// PRINT STATE: current revenues and "split" values for each
	//		starting amount after completing each location
	//		(in tables as done in class)

	// PRINT STATE: final revenue and the plans selected at each location

	// PRINT STATE: run time for the naive test and dynamic test


	// // Read all files from input
	// for (int i = 1; i < argc-1; ++i)
	// {
	// 	// readInput(argv[i]);
	// 	// cb.displayFile(argv[i]);
	// 	cb.readFile(argv[i]);
	// }

	return 0;
}

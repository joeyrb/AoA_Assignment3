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
#include <chrono>
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

// Calculate factorial from 1 (begin) to n (end). Returns factorial and 1 if input = 0;
int calcN(CapitalBudget cb)
{
	int n = 1;
	for (int i = 0; i < cb.getNumLocations(); ++i)
	{
		n = (n) * (cb.getNumProposalsAt(i));
	}
	return n;
}



// Permutations
void PermuteSet(CapitalBudget cb, int location, int size, vector<int> p, vector<bool> used)
{
	int n = cb.getNumProposalsAt(location);
	// int n = calcN(cb);
	if(size >= n)
	{
		for (int i = 0; i < n; ++i)
		{
			cout << cb.getRevenueAt(location, p.at(i)) << " ";
		}
		cout << endl;
		return;
	}

	// Get each permutation for each set
	for(int i = 0; i < n-size; ++i)
	{
		if(!used[i])
		{
			p.at(size) = (cb.getRevenueAt(location,i));
			used[i] = true;
			PermuteSet(cb, location, size, p, used);
			used[i] = false;
		}
	}
}

// TODO: 
//		- Apply the permute set function to iterate through number of locations
void PermuteRec(CapitalBudget cb, int location, int n, int size, vector<int> p, vector<bool> used)
{
	if(size >= n)
	{
		PermuteSet(cb, location, size, p, used);
		return;
	}
	// For each location, find permutations of each set
	for (int i = 0; i < n; ++i)
	{
		if( !used[i] )
		{
			p.at(size) = i;
			used[i] = true;
			PermuteRec(cb, location, n, size+1, p, used);
			used[i] = false;
		}
	}
}

// Dynamic approach
// void dynamicApproach(CapitalBudget cb, int location, int r, int n, int size, vector<int> p, vector<bool> used)
// {
// 	if(size >= n)
// 	{
// 		for (int i = 0; i < n; ++i)
// 		{
// 			cout << cb.getRevenueAt(location, p.at(i)) << " ";
// 		}
// 		cout << endl;
// 		return;
// 	}
// 	// For each location, find permutations of each set
// 	for (int i = 0; i < n-size; ++i)
// 	{
// 		if( !used[i] )
// 		{
// 			if(cb.getAvailableAmount() >= cb.getCostAt(location, i))
// 			{
// 				p.at(i) = cb.getRevenueAt(location, i);
				
// 				cb.setAvailableAmount(cb.getAvailableAmount() - cb.getCostAt(location, i));
// 				used[i] = true;
// 				dynamicApproach(cb, location, n, size+1, p, used);
// 				used[i] = false;
// 			}
// 		}
// 	}
// }


/************************************************************************/
/*****************************MAIN***************************************/
/************************************************************************/

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		printf("Usage: %s file_name start_amount\n", argv[0]);
		return -1;
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
	// Calculate number of all permutations
	// int* n;
	// to find n, multiply the number of proposals together at every location
	// cout << "n! = " << calcN(cb) << endl;
	time_t currTime = time( 0 );
	vector<int> q;
	vector<bool> used;
	int n = 1;
	auto c = chrono::system_clock::now();
	for (int i = 0; i < cb.getNumLocations(); ++i)
	{
		n = cb.getNumProposalsAt(i) * cb.getNumLocations();
		used.resize(cb.getNumProposalsAt(i));
		q.resize(n);

		// Working:
		// PermuteRec(cb, i, cb.getNumProposalsAt(i), 0, q, used);	// Generates n! permutations
		cb.permuteRec(i, cb.getNumProposalsAt(i), 0, q, used);		// Generates n unique permutations (no repeats)

		q.resize(0);
		used.resize(0);
	}
	chrono::duration<double> pBench = chrono::system_clock::now() - c;
	cb.printPermutations();
	
	// Create 2D list of permutations
	cb.setPermutationSets();

	// PRINT STATE: current revenues and "split" values for each
	//		starting amount after completing each location
	//		(in tables as done in class)

	// PRINT STATE: final revenue and the plans selected at each location

	// PRINT STATE: run time for the naive test and dynamic test
	cout << "Permutation benchmark: " << 1000*pBench.count() << " ms\n";
	return 0;
}

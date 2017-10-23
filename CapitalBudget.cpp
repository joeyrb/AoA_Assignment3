#include "CapitalBudget.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/


/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/
CapitalBudget::CapitalBudget()
{
}

/************************************************************************
   Function:		CapitalBudget()
   Author:			Joey Brown
   Description:		Initialize object from a file
   Parameters:		input file from command line
 ************************************************************************/
// TODO: 
// 		- accept the full command line argument list and build from there
CapitalBudget::CapitalBudget(const char* infile)
{
	// Fill contents from command line argument
	readFile(infile);
}

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/
CapitalBudget::~CapitalBudget()
{
}

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:		Safely open a file, return true is file is opened, 
   						false otherwise
   Parameters:
 ************************************************************************/
bool CapitalBudget::openFileIn(fstream &file, string name)
{
	file.open(name.c_str(), ios::in);
	if (file.fail())
		return false;
	else
		return true;
}

/************************************************************************
   Function:		getNums()
   Author:			Joey Brown
   Description:		Extracts a vector of ints from a string and returns 
   						the list as a vector of ints. 
   Parameters:		String of numbers to extract.
 ************************************************************************/
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

/************************************************************************
   Function:		displayFile()
   Author:			Joey Brown
   Description:		Displays the contents of a file from a file object.
   Parameters:		Files object to open and display.
 ************************************************************************/
// Display the contents of a file
void CapitalBudget::displayFile(const char* infile)
{
	fstream file;
	if(openFileIn(file, infile))
	{
		cout << endl << infile << " opened successfully.\n";
		string line;		// Stores text read from txt file
		vector<int> nums;	// Stores ints read from txt file
		int loc_iter = 1;	// Location iterator

		cout << "\nContents: \n";
		cout <<   "------------------------\n";
		
		getline(file,line);
		cout << "Num Locations: " << line << endl;
		while(!file.eof())
		{
			getline(file, line, '\n');
			nums = getNums(line);
			if (nums.size() == 1 ) 
			{
				cout << "\nLocation " << loc_iter << ": " << endl 
						<< nums.at(0) << " proposals\n";
				loc_iter++;
			}
			// Quit processing if reading the end of file
			if(file.eof())
				break;

			// Display contents of text file 
			if(nums.size() > 1)
			{
				for (int i = 0; i < nums.size(); ++i)
				{
					cout << nums.at(i) << " ";
				}
				cout << endl;
			}
		}
		cout <<   "------------------------\n";

		file.close();
	}
	else 
		cout << "File open error" << endl;
	cout << "File closed\n";
}

/************************************************************************
   Function:		readFile()
   Author:			Joey Brown
   Description:		Reads the file from the command line input and sets
   						member variables to corresponding values.
   Parameters:		File name from the command line input.
 ************************************************************************/
void CapitalBudget::readFile(const char* infile)
{
	fstream file;
	if(openFileIn(file, infile))
	{
		string line;		// Stores text read from txt file
		vector<int> nums;	// Stores ints read from txt file
		int curr_proposal = 0; 	// keeps track of current proposal

		// Start with setting the number of locations and resizing vectors
		getline(file, line);
		setNumLocations(line);
		_cost.resize(getNumLocations());
		_revenue.resize(getNumLocations());

		// Assign number of properties and locations when appropriate
		while(!file.eof())
		{
			// Quit processing if reading the end of file
			if(file.eof())
				break;

			// Read line and extract ints
			getline(file, line, '\n');
			nums = getNums(line);

			// Add num proposals at location
			if (nums.size() == 1)
			{
				addNumProposals(nums.at(0));
				// Allocate space for vectors at this location to size = num proposals
				_cost.at(curr_proposal).resize(getNumProposalsAt(curr_proposal));
				_revenue.at(curr_proposal).resize(getNumProposalsAt(curr_proposal));
				
				// 
				for (int i = 0; i < getNumProposalsAt(curr_proposal); ++i)
				{
					// cout << "Test" << endl;
					getline(file, line, '\n');
					nums = getNums(line);
					setCostAt(curr_proposal, i, nums.at(0));
					setRevenueAt(curr_proposal, i, nums.at(1));
				}
				curr_proposal++;
			}
		}
		file.close();
	}
	else 
		cout << "File open error" << endl;
}

/************************************************************************
   Function:		printCosts()
   Author:			Joey Brown
   Description:		Displays all costs to console
   Parameters:		
 ************************************************************************/
void CapitalBudget::printCosts()
{
	for (int i = 0; i < getCostSize(); ++i)
	{
		for (int j = 0; j < getNumCostsAt(i); ++j)
		{
			cout << getCostAt(i,j) << " ";
		}
	}
}

/************************************************************************
   Function:		printRevenue()
   Author:			Joey Brown
   Description:		Displays all revenue to console
   Parameters:
 ************************************************************************/
void CapitalBudget::printRevenue()
{
	for (int i = 0; i < getRevenueSize(); ++i)
	{
		for (int j = 0; j < getNumRevenueAt(i); ++j)
		{
			cout << getRevenueAt(i,j) << " ";
		}
	}
}

/************************************************************************
   Function:		printContents()
   Author:			Joey Brown
   Description:		Displays all contents of object to console
   Parameters:
 ************************************************************************/
void CapitalBudget::printContents()
{
	cout << "\nContents: \n";
	cout <<   "------------------------\n";
	
	cout << "Num Locations: " << getNumLocations() << endl;
	cout << "Start amount: " << getStartAmount() << endl;

	for (int i = 0; i < getNumLocations(); ++i)
	{
		cout << "\nLocation " << i+1 << endl;
		cout << "Proposals: " << getNumProposalsAt(i) << endl;
		cout << "Cost" << "   " << "Revenue\n";
		// cout << "----" << "   -------\n";
		for (int j = 0; j < getNumProposalsAt(i); ++j)
		{
			cout << setw(3) << getCostAt(i,j) << "   " << setw(5) << getRevenueAt(i,j) << endl;
		}
	}
	cout <<   "------------------------\n";
}

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/
void CapitalBudget::printPermutations()
{
	cout << "Permutations: \n";
	for (int i = 0; i < _pList.size(); ++i)
	{
		cout << _pList.at(i) << " ";
	}
		cout << endl;
}

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/
void CapitalBudget::printSplits()
{
 	cout << "Splits: \n";
 	for (int i = 0; i < _split.size(); ++i)
 	{
 		cout << _split.at(i) << " ";
 	}
 	cout << endl;
}

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
************************************************************************/
int* CapitalBudget::vectorToArray(vector<vector<int>> v)
{
	int* arr;
	for(int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < v.at(i).size(); ++j)
		{
			cout << v.at(i).at(j) << endl;
		}
	}
	return arr;
}

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
************************************************************************/
void CapitalBudget::permuteSet(int location, int size, vector<int> p, vector<bool> used)
{
	int n = getNumProposalsAt(location);
	if(size >= n)
	{
		for (int i = 0; i < n; ++i)
		{
			addPermutation(getRevenueAt(location, p.at(i)));
			// cout << getRevenueAt(location, p.at(i)) << " ";
		}
		// cout << endl;
		return;
	}
	for(int i = 0; i < n-size; ++i)
	{
		if(!used[i])
		{
			p.at(size) = (getRevenueAt(location,i));
			used[i] = true;
			permuteSet(location, size+1, p, used);
			used[i] = false;
		}
	}
}

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
************************************************************************/
void CapitalBudget::permuteRec(int location, int n, int size, vector<int> p, vector<bool> used)
{
	if(size >= n)
	{
		addSplit(size-1);
		permuteSet(location, size, p, used);
		return;
	}

	// For each location, find permutations of each set
	for (int i = 0; i < n-size; ++i)
	{
		if( !used[i] )
		{
			p.at(size) = i;
			used[i] = true;
			permuteRec(location, n, size+1, p, used);
			used[i] = false;
		}
	}
}

/************************************************************************
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
************************************************************************/

int factorial(int n)
{
	if (n == 0)
		return 1;
	else
		n = n * factorial(n-1);
}

void CapitalBudget::setPermutationSets()
{
	vector<int>::iterator itStrt;
	itStrt = _pList.begin();
	vector<int>::iterator itEnd;
	itEnd = _pList.begin()+_split.at(0)+1;
	_pSets.resize(_split.size());
	// Create 2D list of choices
	for (int i = 0; i < _split.size(); ++i)
	{
		if(i > 0)
		{
			itStrt = itEnd;
			itEnd = itStrt+_split.at(i)+1;
		}
		_pSets.at(i).resize(_split.at(i));
		_pSets.at(i).assign(itStrt,itEnd);
	}
	cout << endl;
}

void CapitalBudget::permute(int start, int size, vector<int> p, vector<bool> used)
{
	int n = _pList.size();
	
	// If the end of a location is reached, then return
	if (size >= n)
	{
		p.shrink_to_fit();
		for (int i = 0; i < p.size(); ++i)
		{
			cout << p[i] << ' ';
		}
		cout << endl;
		return;
	}

	// Traverse Locations remaining
	for (int i = 0; i < _pSets.at(start).size(); ++i)
	{
		if (!used[i])
		{
			p[i] = (_pSets.at(start).at(size));
			used[i] = true;
			permute(start, size+1, p, used);
			used[i] = false;
		}
	}

}

// void dynamicApproach(int location, int r, int n, int size, vector<int> p, vector<bool> used)
// {
// 	if(size >= n)
// 	{
// 		// 
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
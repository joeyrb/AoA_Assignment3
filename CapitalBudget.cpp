#include "CapitalBudget.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

/************************************************************************
   Function:
   Author:
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
   Function:
   Author:			Joey Brown
   Description:
   Parameters:
 ************************************************************************/
// Initialize object from a file
CapitalBudget::CapitalBudget(const char* infile)
{
	fstream file;
	if(openFileIn(file, infile))
	{
		cout << endl << infile << " opened successfully.\n";
		// displayFile(file);
		file.close();
	}
	else 
		cout << "File open error" << endl;
	cout << "\nFile closed\n";
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
	cout << "\nFile closed\n";
}

/************************************************************************
   Function:		readFile()
   Author:			Joey Brown
   Description:		Reads the file from the command line input.
   Parameters:		File name from the command line input.
 ************************************************************************/
// Read a file
void CapitalBudget::readFile(const char* infile)
{
	fstream file;
	if(openFileIn(file, infile))
	{
		cout << endl << infile << " opened successfully.\n";
		string line;		// Stores text read from txt file
		vector<int> nums;	// Stores ints read from txt file
		int curr_proposal = 0; 	// keeps track of current proposal

		// Start with setting the number of locations
		getline(file, line);
		setNumLocations(line);

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
				appendNumProposals(nums.at(0));
				vector<int> costVect;
				vector<int> revVect;
				while(!file.eof() && nums.size() > 1)
				{
					getline(file, line, '\n');
					nums = getNums(line);
					// set cost nums.at(0)
					costVect.push_back(nums.at(0));
					// set revenue nums.at(1)
					revVect.push_back(nums.at(1));
					addCostAt(curr_proposal, nums.at(0));
					addRevenueAt(curr_proposal, nums.at(0));
				}
				curr_proposal++;
			}


			// Store contents of text file at current proposal
			if(nums.size() > 0)
			{
				for (int i = 0; i < nums.size(); ++i)
				{
					// set cost nums.at(0)
					addCostAt(curr_proposal-1, nums.at(i));
					// set revenue nums.at(1)
					addCostAt(curr_proposal-1, nums.at(i));
				}
			}
		}
		
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
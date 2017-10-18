#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class CapitalBudget
{
public:
	CapitalBudget();				// Default Constructor
	CapitalBudget(fstream &file);	// Initialize with a file
	~CapitalBudget();

	// Methods
	bool openFileIn(fstream &file, string name);
	vector<int> getNums(string str);
	void displayFile(fstream &file);
	void readFile(const char* infile);
	// void readFile(string infile);
	// void readFile(fstream &file);



	// Accessors
	int getNumLocations() { return _nLoc; }
	
	vector<int> getNumProposals() { return _numProp; }
	int getNumProposalsAt(int i) { return _numProp.at(i); }
	
	vector<vector<int>> getCosts() { return _cost; }
	int getNumCostsAt(int i) { return _cost.at(i).size(); }

	vector<vector<int>> getRevenue() { return _revenue; }
	int getNumRevenueAt(int i) { return _revenue.at(i).size(); }



	// Mutators
	void setNumLocations(int n) { _nLoc = n; }
	void setNumLocations(string str) { _nLoc = stoi(str); }
	void setNumProposalsAt(int i, int n) { _numProp.at(i) = n; } 
	void setCostAt(int i, int j, int val) { _cost[i][j] = val; }
	void setRevenueAt(int i, int j, int val) { _revenue[i][j] = val; }

private:
	int _nLoc;						// Total number of locations
	vector<int> _numProp;			// Number of proposals per location
	vector<vector<int>> _cost;		// 2D vector of cost per location
	vector<vector<int>> _revenue;			// 2D vector of revenue per location
};
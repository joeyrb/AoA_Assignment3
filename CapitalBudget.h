#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class CapitalBudget
{
public:

	// Constructors & Destructors
	CapitalBudget();						// Default Constructor
	CapitalBudget(const char* filename);	// Initialize with a file name 
	~CapitalBudget();

	// Methods
	bool openFileIn(fstream &file, string name);
	vector<int> getNums(string str);
	void displayFile(const char* infile);
	void readFile(const char* infile);



	// Accessors
	int getStartAmount(){ return _startAmnt; }

	int getNumLocations() { return _nLoc; }
	
	vector<int> getNumProposals() { return _numProp; }
	int getNumProposalsAt(int i) { return _numProp.at(i); }
	
	vector<vector<int>> getCosts() { return _cost; }
	int getNumCostsAt(int i) { return _cost.at(i).size(); }

	vector<vector<int>> getRevenue() { return _revenue; }
	int getNumRevenueAt(int i) { return _revenue.at(i).size(); }



	// Mutators
	void setStartAmount( int val ) { _startAmnt = val; }
	
	void setNumLocations(int n) { _nLoc = n; }
	void setNumLocations(string str) { _nLoc = stoi(str); }
	
	void setNumProposalsAt(int i, int n) { _numProp.at(i) = n; } 
	void appendNumProposals(int num) { _numProp.push_back(num); }
	
	void setCostAt(int i, int j, int val) { _cost[i][j] = val; }
	void addCostAt(int i, int val) { _cost[i].push_back(val); }
	
	void setRevenueAt(int i, int j, int val) { _revenue[i][j] = val; }
	void addRevenueAt(int i, int val) { _revenue[i].push_back(val); }

private:
	int _startAmnt;					// Starting amount
	int _nLoc;						// Total number of locations
	vector<int> _numProp;			// Number of proposals per location
	vector<vector<int>> _cost;		// 2D vector of cost per location
	vector<vector<int>> _revenue;			// 2D vector of revenue per location
};
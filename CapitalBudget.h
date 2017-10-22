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
	void printCosts();
	void printRevenue();
	void printContents();


	// Accessors
	int getStartAmount() { return _startAmnt; }							// Starting amount

	int getAvailableAmount() { return _amntAvail; }						// Available amount

	int getNumLocations() { return _nLoc; }								// Num locations
	
	vector<int> getProposals() { return _numProp; }					// Num proposals
	int getNumProposalsAt(int i) { return _numProp.at(i); }
	
	vector<vector<int>> getCosts() { return _cost; }					// Cost
	int getCostSize() { return _cost.size(); }
	int getCostAt(int i, int j) { return _cost.at(i).at(j); }
	int getNumCostsAt(int i) { return _cost.at(i).size(); }

	vector<vector<int>> getRevenue() { return _revenue; }				// Revenue
	int getRevenueSize() { return _revenue.size(); }
	int getRevenueAt(int i, int j) { return _revenue.at(i).at(j); }
	int getNumRevenueAt(int i) { return _revenue.at(i).size(); }



	// Mutators
	void setStartAmount( int val ) { _startAmnt = val; }				// Starting amount

	void setAvailableAmount(int val) { _amntAvail = val; }						// Available amount
	
	void setNumLocations(int n) { _nLoc = n; }							// Num Locations
	void setNumLocations(string str) { _nLoc = stoi(str); }
	
	void setNumProposalsAt(int i, int n) { _numProp.at(i) = n; } 		// Num Proposals
	void addNumProposals(int num) { _numProp.push_back(num); }
	
	void setCostAt(int i, int j, int val) { _cost[i][j] = val; }		// Cost
	void addCostAt(int i, int val) { _cost[i].push_back(val); }
	
	void setRevenueAt(int i, int j, int val) { _revenue[i][j] = val; }	// Revenue
	void addRevenueAt(int i, int val) { _revenue[i].push_back(val); }

private:
	int _startAmnt;					// Starting amount
	int _amntAvail;					// Available amount
	int _nLoc;						// Total number of locations
	vector<int> _numProp;			// Number of proposals per location
	vector<vector<int>> _cost;		// 2D vector of cost per location
	vector<vector<int>> _revenue;			// 2D vector of revenue per location
};
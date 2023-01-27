#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <string>
#include <unordered_map> //hashtable
#include <unordered_set>

using namespace std;

struct puzzleNode {
	vector<vector<int>> state;
	int cost;
	int heu;
	int priority;

	bool operator<(const puzzleNode& b) const {
		return priority < b.priority;
	}
};

class Solver {

private:
	int currentCost;
	vector<vector<int>> currentState;
	vector<vector<int>> goalState;
	priority_queue<puzzleNode> frontier;
	unordered_map<int, puzzleNode> exploredSet;
	vector<vector<int>> swapTile(vector<vector<int>> cur, int id, int rid, int cid); 
	void nodeBuilder(vector<vector<int>> cur, int cost);
	int heuristic(vector<vector<int>> cur, int heu = 0, int x = 0, int y = 0);
	void expandStates();
	void prepHash();
	void display(vector<vector<int>> currentState);
	int genKey(vector<vector<int>> cur);

public:
	Solver();
	Solver(vector<vector<int>> init, vector<vector<int>> goal);
	void solve();
};
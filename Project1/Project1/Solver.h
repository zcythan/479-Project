#pragma once
#include "Puzzle.h"
#include <queue>
#include <iostream>
#include <string>

struct puzzleNode {
	vector<vector<int>> state;
	int cost;
	int heu;
	int priority; //set equal to calculation between cost and heu

	bool operator<(const puzzleNode& b) const {
		return priority < b.priority;
	}
};

class Solver {

private:
	vector<vector<int>> currentState;
	vector<vector<int>> goalState;
	priority_queue<puzzleNode> frontier;
	vector<vector<int>> swapTile(vector<vector<int>> cur, int id, int rid, int cid); //internal use only
	void nodeBuilder(vector<vector<int>> cur, int cost);

public:
	Solver();
	Solver(Puzzle p, vector<vector<int>> goal);
	void expandStates();
	void printNodes();
};
#include "Solver.h"

Solver::Solver() {
	cout << "Invalid object used as input" << endl;
}

Solver::Solver(Puzzle p, vector<vector<int>> goal) {
	currentState = p.getState();
	goalState = goal;
}

vector<vector<int>> Solver::swapTile(vector<vector<int>> cur, int id, int rid, int cid) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (cur[i][j] == id) {
				cur[i][j] = 0;
				break;
			}
		}
	}
	cur[rid][cid] = id;
	return cur;
}


void Solver::nodeBuilder(vector<vector<int>> cur, int cost) {

	int heu = 0; //heu function
	int pri = 0; //calculate priority

	puzzleNode pn = { cur, cost, heu, pri };
	frontier.push(pn);
}

void Solver::printNodes() {
		vector<vector<int>> cur = frontier.top().state;
		for (int i = 0; i < 3; i++) {
			string curRow = "";
			for (int j = 0; j < 3; j++) {
				if (cur[i][j] == 0) {
					curRow += "-";
					continue;
				}
				curRow += to_string(cur[i][j]);
			}
			cout << curRow << endl;
		}
		cout << frontier.top().cost;
		frontier.pop();
		cout << endl;

		while (!frontier.empty())
			frontier.pop();
}

void display(vector<vector<int>> cur) {
	for (int i = 0; i < 3; i++) {
		string curRow = "";
		for (int j = 0; j < 3; j++) {
			if (cur[i][j] == 0) {
				curRow += "-";
				continue;
			}
			curRow += to_string(cur[i][j]);
		}
		cout << curRow << endl;
	}
	cout << endl;
}


void Solver::expandStates() {
	//generate vectors representing all states of possible move from the current state.
	int row, col;
	int maxOutcomes = 4;
	//North, east, south, west
	bool allowedDir[4] = { true, true, true, true };
	//step one, find the blank tile
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (currentState[i][j] == 0) {
				row = i + 1;
				col = j + 1;
				break;
			}
		}
	}

	//find number of child nodes that need to be generated.
	if (col == 1) {
		maxOutcomes--;
		allowedDir[3] = false;
	}
	if (row == 1) {
		maxOutcomes--;
		allowedDir[0] = false;
	}
	if (col == 3) {
		maxOutcomes--;
		allowedDir[1] = false;
	}
	if (row == 3) {
		maxOutcomes--;
		allowedDir[2] = false;
	}
	//generate them
	//maybe push them into a vector or something, a vector containing vectors. for now lets just generate and print. 
	
	int rid = row - 1;
	int cid = col - 1;

	if (allowedDir[3]) {
		cout << currentState[rid][cid - 1]; //cost of 2
	}
	if (allowedDir[0]) {
		nodeBuilder(swapTile(currentState, currentState[rid - 1][cid], rid, cid), 1); // then print the return from a display function.
	}
	if (allowedDir[1]) {
		nodeBuilder(swapTile(currentState, currentState[rid][cid + 1], rid, cid), 2);
	}
	if (allowedDir[2]) {
		cout << currentState[rid+1][cid]; //cost of 3
	}
	

}
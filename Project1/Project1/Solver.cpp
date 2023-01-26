#include "Solver.h"

Solver::Solver() {
	currentCost = 0;
	cout << "Invalid object used as input" << endl;
}

void Solver::display(vector<vector<int>> currentState) { //User interface design would go here.
	for (int i = 0; i < 3; i++) {
		string curRow = "";
		for (int j = 0; j < 3; j++) {
			if (currentState[i][j] == 0) {
				curRow += "-";
				continue;
			}
			curRow += to_string(currentState[i][j]);
		}
		cout << curRow << endl;
	}
	if(!frontier.empty())
		cout << frontier.top().cost << " " << frontier.top().heu << " " << frontier.top().priority << endl;
	cout << endl;
}


Solver::Solver(vector<vector<int>> init, vector<vector<int>> goal) {
	currentState = init;
	currentCost = 0;
	goalState = goal;
	display(currentState); //prints initial state.
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

int Solver::heuristic(vector<vector<int>> cur, int heu, int x, int y) {
	if (x == 3 && y == 3)
		return heu;
	if (y == 3) 
		y = 0;
	
	int curID = cur[x][y];

	int goalCords[2] = { 0, 0 };
	int temp = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (goalState[i][j] == curID) {
				goalCords[0] = i;
				goalCords[1] = j;
				break;
			}
		}
	}

	//logic for calculating the number of steps/ in what direction.
	int deltaX = x - goalCords[0]; //Chance's heuristic logic.
	int deltaY = y - goalCords[1];
	if (curID != 0) {
		if (deltaX > 0) {
			temp += (deltaX * 3);
		}
		if (deltaX < 0) {
			temp += abs(deltaX);
		}
		if (deltaY > 0) {
			temp += (deltaY * 2);
		}
		if (deltaY < 0) {
			temp += (abs(deltaY) * 2);
		}
	}
	y++;
	if (y == 3)
		x++;
	return heuristic(cur, heu+temp, x, y);
}

void Solver::nodeBuilder(vector<vector<int>> cur, int cost) {
	int heu = heuristic(cur); //heu function
	int eval = ((currentCost + cost) + heu);
	int pri = abs(100 - eval);//(((100-eval)*(10-1))/100); //calculate priority

	puzzleNode pn = { cur, (currentCost + cost), heu, pri };
	frontier.push(pn); //add nodes to frontier set
}

void Solver::prepHash() { //name of this function is irrelevant. Change it at some point.
	while (!frontier.empty()) {
		vector<vector<int>> cur = frontier.top().state;

		display(cur); //will be moved once hash table is implemented.
		

		//check if frontier.top() is in the exploredSet.
		//If the first node is NOT in the explored set, then add it, update the currentState to equal frontier.top.state() and pop.
		//Then, check all other entries in frontier, if they aren't in the exploredSet, add them and then pop. 
		// 
		//If the first node IS in the explored set, then just pop it and check the next top. 
		//Keep popping until it finds a node not in the set, then set it to currentState, add to exploredSet and pop. 
		// 
		//ALSO use currentCost+= frontier.top().cost at the same time you reassign the currentState value, call the display(cur) function here too. 
		

		frontier.pop();
		//cout << endl;
	}
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
		nodeBuilder(swapTile(currentState, currentState[rid][cid - 1], rid, cid), 2);
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

void Solver::solve() {
	//When ready, add a while loop that runs until currentState == goalState.
	expandStates();
	prepHash();
}
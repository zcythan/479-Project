#include "Solver.h"

Solver::Solver() {
	currentCost = 0;
	lastPri = 0;
	expNum = 0;
	cout << "Invalid object used as input" << endl;
}

void Solver::display(vector<vector<int>> cur) { //User interface design would go here.
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
		if (!frontier.empty()) {
			cout << frontier.top().cost << " " << frontier.top().heu << " " << expNum << endl;
		}
		else {
			cout << 0 << " " << heuristic(currentState) << " " << expNum << endl;
		}
		cout << endl;
		expNum++;
}

Solver::Solver(vector<vector<int>> init, vector<vector<int>> goal) {
	currentState = init;
	currentCost = 0;
	expNum = 1;
	lastPri = 0;
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

	//logic for calculating the number of steps/in what direction.
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

int Solver::genKey(vector<vector<int>> cur) {
	string temp = "0";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			temp += to_string(cur[i][j]);
		}
	}
	return stoi(temp);
}

void Solver::nodeBuilder(vector<vector<int>> cur, int cost) {
	int heu = heuristic(cur); //heu function
	int eval = ((currentCost + cost) + heu); // f(n) 
	int pri = abs(100 - eval);
	int key = genKey(cur);

	if (exploredSet.empty() || exploredSet.find(key) == exploredSet.end()) {
		puzzleNode pn = { cur, (currentCost + cost), heu, pri };
		frontier.push(pn); //add nodes to frontier set
	}
	
}  

void Solver::prepHash() { //name of this function is irrelevant. Change it at some point.
	// Get the current state from the top of the priority queue
	vector<vector<int>> cur = frontier.top().state;
	int hash = genKey(cur);

	// Taking top node, updating global values, saving to hash table 
	exploredSet.emplace(hash, frontier.top());
	currentCost = frontier.top().cost;
	currentState = cur;
	lastPri = frontier.top().priority;
	display(cur);
	frontier.pop();

	while (!frontier.empty()) {
		if (frontier.top().priority == lastPri) {
			display(frontier.top().state);
			overflow.push(frontier.top());
		}
			cur = frontier.top().state;
			hash = genKey(cur);
			exploredSet.emplace(hash, frontier.top());
			frontier.pop();
	} 
}

void Solver::expandStates() {
	//generate vectors representing all states of possible move from the current state.
	int row, col;
	//North, east, south, west
	bool allowedDir[4] = { true, true, true, true };
	//find the blank tile
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
		allowedDir[3] = false;
	}
	if (row == 1) {
		allowedDir[0] = false;
	}
	if (col == 3) {
		allowedDir[1] = false;
	}
	if (row == 3) {
		allowedDir[2] = false;
	}

	//generate them
	int rid = row - 1;
	int cid = col - 1;

	if (allowedDir[3]) {
		nodeBuilder(swapTile(currentState, currentState[rid][cid - 1], rid, cid), 2);
	}
	if (allowedDir[0]) {
		nodeBuilder(swapTile(currentState, currentState[rid - 1][cid], rid, cid), 1);
	}
	if (allowedDir[1]) {
		nodeBuilder(swapTile(currentState, currentState[rid][cid + 1], rid, cid), 2);
	}
	if (allowedDir[2]) {
		nodeBuilder(swapTile(currentState, currentState[rid + 1][cid], rid, cid), 3);
	}
}

void Solver::solve() {
	//When ready, add a while loop that runs until currentState == goalState.
	while(currentState != goalState){
		expandStates();
		while (!overflow.empty()) {
			currentState = overflow.top().state;
			currentCost = overflow.top().cost;
			expandStates();
			overflow.pop();
		}
		prepHash();
	}
}
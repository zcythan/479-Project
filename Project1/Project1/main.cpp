#include "Header.h"

using namespace std;

struct puzzleNode {

	// Ties to nearby nodes
	// Ordered according to instructions
	// Populate with data in this order

	// 0 = Wall, can't move
	int ID;
	int priority;
	int initX, initY;
	int endX, endY;
	std::string moveDirections;

	bool operator<(const puzzleNode &b) const {
		return priority < b.priority;
	}
};


int main() {
	priority_queue<puzzleNode> pq;

	puzzleNode a = puzzleNode();
	a.priority = 1;

	puzzleNode b = puzzleNode();
	b.priority = 2;

	puzzleNode c = puzzleNode();
	c.priority = 3;


	pq.push(a);
	pq.push(b);
	pq.push(c);

	for (int i = 0; i < 3; i++) {
		cout << pq.top().priority << endl;
		pq.pop();
	}

	return 0;
}

void getDirections(puzzleNode a) {
	// Returns shortest path of "<num of moves><direction>"
	int deltaX = a.endX - a.initX;
	int deltaY = a.endY - a.initY;

	// West
	if (deltaX > 0) {
		a.moveDirections += std::to_string(deltaX % 3) + 'W';
	}
	// Does not move
	else if (deltaX == 0) {
		a.moveDirections += "0E";
	}
	else if (deltaX < 0) {
		a.moveDirections += std::to_string(abs(deltaX % 3)) + 'E';
	}
	// South
	if (deltaY > 0) {
		a.moveDirections += std::to_string(deltaY % 3) + 'S';
	}
	// Staying
	else if (deltaY == 0) {
		a.moveDirections += "0N";
	}
	// North
	else if (deltaY < 0) {
		a.moveDirections += std::to_string(abs(deltaY % 3)) + 'N';
	}
}

/*
// Unfinished
// Heuristic Function
int countMoves(puzzleNode Ident) {
	int Moves;
	// Minimum moves:
	// 1 = 2 West
	// 2 = 1 South
	// 3 = 0, Stays
	// 4 = 0, Stays
	// 5 = 1 South

	switch (Ident.ID) {
	case 0:
		// This means something busted
		// Because 0 is a number we might need, picked -1.
		return -1;
		break;
	case 1:
		return 2;
		break;
	case 3:
		return 0;
		break;
	case 4:
		return 0;
		break;
	case 5:
		return 1;
		break;
		// Not sure how to handle these in a simple manner
		// Considered returning a char as a flag to follow more complicated logic
		// Also considered adding a int in the node as a flag, decrement node after dir change
		// Could decrement in the calcCost function, and then have the calcCost function call
		// this function a second time.
		// while(Ident.DirChanges != 0)...
		// 6 = 1 South -> 1 West
		// 7 = 1 North -> 1 West
		// 8 = 1 East -> 1 South
	case 6:
		return 2;
		break;
	case 7:
		return 2;
		break;
	case 8:
		return 2;
		break;
	}
	return Moves;
}

// Pass a node, its calculated cost, and number of moves it needs to make to 
// Get to the end-goal
// Unfinished
void CalcPriority(puzzleNode Ident, int Cost, int Moves) {
	// f(n) = g(n) + h(n)
	// g(n) = Cost
	// h(n) = Heuristic function
	int Priority = 10; // Priority = f(n), lower is better

	Ident.priority = Priority;
}

// Pass this a node and which direction you are testing
// Number = Direction: 1=N 2=E 3=S 4=W 
// Returns 0 if you can't move
int calcCost(puzzleNode Ident, int Dir) {
	// Open to suggestions to change this
	// Costs: S = 1, E = W = 2, N = 3

	int Cost = 0;
	switch (Dir) {
		// 1 = North
	case 1:
		if (Ident.North == 0)
			return 0;
		Cost = Cost + 3;
		break;
		// 2 = East
	case 2:
		if (Ident.East == 0)
			return 0;
		Cost = Cost + 2;
		break;
		// 3 = South
	case 3:
		if (Ident.South == 0)
			return 0;
		Cost = Cost + 1;
		break;
		// 4 = West
	case 4:
		if (Ident.West == 0)
			return 0;
		Cost = Cost + 2;
		break;
	}
	return Cost;
}
*/
#include "Solver.h"

Solver::Solver() {

}

Solver::Solver(Puzzle p) {
	currentState = p.getState();
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
				row = i+1;
				col = j+1;
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
		allowedDir[1] = false;
	}
	if (row == 3) {
		allowedDir[2] = false;
	}
	//generate them
	//maybe push them into a vector or something, a vector containing vectors. for now lets just generate and print. 
	for (int i = 0; i < maxOutcomes; i++) {

	}

	
}
#include "Puzzle.h"

Puzzle::Puzzle() {
	
	state.resize(3);

	for (int i = 0; i < 3; i++) {
		state[i].resize(3);
	}

	state[0][0] = 1;
	state[0][1] = 6;
	state[0][2] = 2;
	state[1][0] = 5;
	state[1][1] = 7;
	state[1][2] = 6;
	state[2][0] = 0;
	state[2][1] = 4;
	state[2][2] = 3;
	
}

void Puzzle::display() {
	for (int i = 0; i < 3; i++) {
		string curRow = "";
		for (int j = 0; j < 3; j++) {
			if (state[i][j] == 0) {
				curRow += "-";
				continue;
			}
			curRow += to_string(state[i][j]);
		}
		cout << curRow << endl;
	}
	cout << endl;
}

vector<vector<int>> Puzzle::getState() {
	return state;
}
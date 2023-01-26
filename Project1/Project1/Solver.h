#pragma once
#include "Puzzle.h"
#include <queue>
#include <iostream>
#include <string>


class Solver {

private:
	vector<vector<int>> currentState;

public:
	Solver();
	Solver(Puzzle p);
	void expandStates();
};
#include "Puzzle.h"
#include "Solver.h"
using namespace std;




int main() {
	vector<vector<int>> goalState = {
		{7,8,1},
		{6,0,2},
		{5,4,3}
	};

	Puzzle p1 = Puzzle();
	Solver s1 = Solver(p1, goalState);
	p1.display();
	s1.expandStates();
	s1.printNodes();
	return 0;
}




#include "Puzzle.h"
#include "Solver.h"
using namespace std;




int main() {
	Puzzle p1 = Puzzle();
	Solver s1 = Solver(p1);
	p1.display();
	s1.expandStates();

	return 0;
}




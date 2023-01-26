#include "Solver.h"
using namespace std;
//All comments that were here before are now in the comments.cpp file.
int main() {
	//0 represents the hash mark.
	vector<vector<int>> goalState = {
		{7,8,1},
		{6,0,2},
		{5,4,3}
	};

	vector<vector<int>> initState = {
		{1,6,2},
		{5,7,8},
		{0,4,3}
	};

	Solver s1 = Solver(initState, goalState);
	s1.solve();
	return 0;
}




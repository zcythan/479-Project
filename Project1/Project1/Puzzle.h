#pragma once
#include <queue>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Puzzle {
private: 
	vector<vector<int>> state; //stores the current state of the puzzle

public: 

	Puzzle(); //constructor.
	void display(); // displays current state of puzzle to console. 
	vector<vector<int>> getState();
	
	//maybe add a function to get and one to alter the state of the puzzle. 

};
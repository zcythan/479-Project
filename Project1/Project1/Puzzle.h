#pragma once
#include <queue>
#include <iostream>
#include <string>

using namespace std;


class Puzzle {
private: 
	int state[3][3]; //stores the current state of the puzzle

public: 

	Puzzle(); //constructor.
	void display(); // displays current state of puzzle to console. 
	
	//maybe add a function to get and one to alter the state of the puzzle. 

};
#pragma once
#include <iostream>

using namespace std;

class Player{
	string name;
	char marker;

public:
	Player(string name, char marker);
	string get_name();
	char get_marker();
};


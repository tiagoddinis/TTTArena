#pragma once
#include <iostream>

using namespace std;

class BoardManager{
	int winLineSize;
	int height;
	int width;
	char** board;
	char* boardLine;

public:
	BoardManager(int height, int width);
	int get_width();
	int get_height();
	void set_win_line_size(int size);
	void clean_board();
	void print_board();
	void print_board_line();
	int place_marker(int row, int column, char playerMarker);
	int check_if_won();
	int get_min_dimension();
};


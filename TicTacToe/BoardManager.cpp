#include "BoardManager.h"

BoardManager::BoardManager(int h, int w){
	height = h;
	width = w;
	board = new char*[h];
	boardLine = new char[(w*2)+1];
	

	for (int i = 0; i < h; i++){
		board[i] = new char[w];
		for (int j = 0; j < w; j++)
			board[i][j] = ' ';
	}

	for (int i = ((w*2)+1); i > 0 ; i--)
		boardLine[i] = '-';

}

int BoardManager::get_width(){
	return width;
}

int BoardManager::get_height(){
	return height;
}

void BoardManager::set_win_line_size(int s){
	winLineSize = s;
}

void BoardManager::clean_board(){
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			board[i][j] = ' ';
}

void BoardManager::print_board(){
	cout << endl << "   ";
	for (int i = 0; i < width; i++)
		cout << i << " ";

	print_board_line();

	for (int i = 0; i < height; i++){
		cout << i << " |";
		for (int j = 0; j < width; j++)
			cout << board[i][j] << "|";
		print_board_line();
	}
}

void BoardManager::print_board_line(){
	cout << endl << "  ";
	for (int i = ((width * 2)+1); i > 0; i--)
		cout << boardLine[i];
	cout << endl;
}

int BoardManager::get_min_dimension(){
	return (height < width)? height : width;
}

int BoardManager::place_marker(int r, int c, char playerMarker){
	if ( (r <= width) && (c <= height) && (board[r][c] == ' ')){
		board[r][c] = playerMarker;
		return 1;
	}
	else return 0;
}

int BoardManager::check_if_won(){
	int row, col, rAux, cAux, cnt = 1;
	int maxWinWidth = (width - winLineSize) + 1;
	int maxWinHeight = (height - winLineSize) + 1;
	char marker;
	bool colSweep = true;
	
	//check horizontally
	for (row = 0; row < height; row++){
		for (cnt = 1, col = 0; col < (width-1); col++){
			marker = board[row][col];
			if ((marker != ' ') && (marker == board[row][col + 1])){
				cnt++;
				if (cnt == winLineSize)
					return 1;
			}
			else if (col == maxWinWidth)
				break;
		}
	}

	//check vertically
	for (col = 0; col < width; col++){
		for (cnt = 1, row = 0; row < (height-1); row++){
			marker = board[row][col];
			if ((marker != ' ') && (marker == board[row + 1][col])){
				cnt++;
				if (cnt == winLineSize)
					return 1;
			}
			else if (row == maxWinHeight)
				break;
		}
	}

	//check diagonally	#
	//					  #
	for (row = 0, col = 0; row < maxWinHeight;){
		for (cnt = 1, rAux = row, cAux = col; (rAux < (height - 1)) && (cAux < (width - 1)); rAux++, cAux++){
			marker = board[rAux][cAux];
			if ((marker != ' ') && (marker == board[rAux + 1][cAux + 1])){
				cnt++;
				if (cnt == winLineSize)
					return 1;
			}
			else if ((cAux == maxWinWidth) || (rAux == maxWinHeight))
				break;
		}

		if (colSweep && (col < maxWinWidth))
			col++;
		else{
			colSweep = false;
			col = 0;
			row++;
		}

	}

	colSweep = true;

	//check diagonally	  #
	//					#
	for (row = (height-1), col = 0; row > (height - maxWinHeight - 1);){
		for (cnt = 1, rAux = row, cAux = col; (rAux >  0) && (cAux < (width - 1)); rAux--, cAux++){
			marker = board[rAux][cAux];
			if ((marker != ' ') && (marker == board[rAux - 1][cAux + 1])){
				cnt++;
				if (cnt == winLineSize)
					return 1;
			}
			else if ((cAux == maxWinWidth) || (rAux == (height - maxWinHeight - 1)))
				break;
		}

		if (colSweep && (col < maxWinWidth))
			col++;
		else{
			colSweep = false;
			col = 0;
			row--;
		}

	}

	return 0;
}
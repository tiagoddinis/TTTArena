#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "BoardManager.h"

using namespace std;

bool available_marker(vector<Player> players, char c);
char get_y_or_n();
int get_int_min_max(int min, int max);
void draw_separator();

int main() {
	bool invalidPosition = true;
	int row = -1, column = -1;
	char cInput;
	string strInput;
	vector<Player> players;

	cout << "Greetings, good gentles/ladies!\nThou art welcome to ye TicTacToe Arena!\nCome hither." << endl;

	//Fill player list
	for (int i = 1;; i++) {
		cout << "\nPlayer " << i << ", what be thy nameth?" << endl;

		if (i > 1)
			cin.ignore();
		getline(cin, strInput);

		cout << "And what shalt be thy marker?" << endl;

		for (bool canProceed = false; !canProceed;){
			while (!(cInput = getchar()))
				cout << "Invalid Input" << endl;

			if (available_marker(players, cInput))
				canProceed = true;
			else{
				cout << "Nay, that maker is taken!\nAgain, what shalt be thy marker?" << endl;
				cin.clear();
				cin.ignore(256, '\n');
			}
		}

		players.push_back( Player(strInput, cInput) );

		cout << "Right, shalt moo players joineth ye fray? (y/n)" << endl;
		cInput = get_y_or_n();

		if (cInput == 'n')
			break;
	}

	//Board Creation
	int ah, aw;
	draw_separator();
	cout << endl << endl << "Ye arena height, I bid thee? 2~9" << endl;
	ah = get_int_min_max(2, 9);
	cout << "Arena width? 2~9" << endl;
	aw = get_int_min_max(2, 9);

	BoardManager bm(ah, aw);

	cout << "\nBeholdeth ye arena!" << endl;

	bm.print_board();

	cout << "\n\nHow longeth shouldst the wineth patt'rn be?  2~" << bm.get_min_dimension() << endl;
	bm.set_win_line_size( get_int_min_max(2, bm.get_min_dimension() ) );

	draw_separator();

	cout << "Have at thee!!\n" << endl;

	//Game Loop
	while (true){
		static unsigned int i;
		
		//Player Turn Loop
		for (i = 0; i < players.size(); i++, invalidPosition = true){
			draw_separator();
			bm.print_board();
			cout << "\n" << players[i].get_name() << "'s turneth\n" << endl;

			while (invalidPosition){
				cout << "Row coordinateth: ";
				row = get_int_min_max(0, bm.get_height() - 1);
				cout << "Column coordinateth: ";
				column = get_int_min_max(0, bm.get_width() - 1);

				if (bm.place_marker(row, column, players[i].get_marker())){

					//if player won
					if (bm.check_if_won()){
						draw_separator();
						cout << "\n" << players[i].get_name() << " hath won!! Huzzah!\n" << endl;
						bm.print_board();
						cout << "\nOne more game, perchance ? (y / n)" << endl;

						cInput = get_y_or_n();
						if (cInput == 'y')
							bm.clean_board();
						else{
							cout << "\n\nFare well.\n" << endl;
							return 0;
						}
					}

					invalidPosition = false;
				}
				else
					cout << "\nThou shalt naught place thou marker thither.\n" << endl;
			}
		}
	}


	return 0;
}

char get_y_or_n(){
	bool invalidInput = true;
	char res;

	while (invalidInput){
		cin >> res;

		if (cin && ((res == 'y') || (res == 'n')) )
			invalidInput = false;
		else{
			cout << "y or n required to proceed. Try again: ";
			cin.clear();
			cin.ignore(256, '\n');
		}
	}

	return res;
}


bool available_marker(vector<Player> players, char c){
	for (vector<Player>::iterator it = players.begin(); it != players.end(); ++it)
		if (it->get_marker() == c)
			return false;

	return true;
}

int get_int_min_max(int min, int max){
	bool invalidInput = true;
	int res;
	
	while (invalidInput){
		cin >> res;
		res = tolower(res);
		if (cin && (res >= min) && (res <= max))
			invalidInput = false;
		else{
			cout << "\nA number between " << min << " and " << max << " is required to proceed.\nTry again: ";
			cin.clear();
			cin.ignore(256, '\n');
		}
	}

	return res;
}

void draw_separator(){
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
}
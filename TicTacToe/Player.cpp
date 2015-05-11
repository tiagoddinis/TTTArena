#include "Player.h"

Player::Player(string n, char m){
	name = n;
	marker = m;
}

string Player::get_name(){
	return name;
}

char Player::get_marker(){
	return marker;
}

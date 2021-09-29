#pragma once
#include <string>
#include <vector>
#include "Game.h"
#include "Exceptions.h"
using std::string;
using std::vector;


class Validator
{
private:
	vector < string > enum_state;

public:
	Validator() {
		enum_state.push_back("Neinceput");
		enum_state.push_back("In derulare");
		enum_state.push_back("Terminat");
	}

	/*
	* validate an existing game
	* Input:game-a Game
	* Output:-
	* Method throws GameError exceptions
	*/
	void validate(const Game& game);

	/*
	* validate a new game
	* Input:game-a Game
	* Output:-
	* Method throws  GameError exceptions
	*/
	void start_validate(const Game& game);
};


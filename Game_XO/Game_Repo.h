#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Game.h"
#include "Exceptions.h"
using std::string;
using std::vector;

class Game_Repo
{

private:
	vector < Game > repo;
	string filename;

	/*
	* The method splits a string according to its delimiter character:' '
	* Input:a string
	* Output: a vector of parts of the original string after spliting 
	*/
	vector < string > split_string(string S);

	//the method loads all data from the file 'filename' in memory
	void loadfromfile();

	//the method loads all data from memory to the file 'filename;
	void storetofile();

public:

	Game_Repo(const string& filename) :filename{ filename } {
		loadfromfile();
	}

	Game_Repo(const Game_Repo&) = delete;

	/*
	* The method add a new game 
	* Input:game-a Game
	* Output:the game will be push into the repo
	* Throw RepoError if the game exists
	*/
	Game add_game(const Game& game);

	/*
	* The method update a game
	* Input:game-a Game 
	* Output:that game will be updated in repository and return the previous game before updating
	* Throw RepoError if the game doesn't exists
	*/
	Game update_game(const Game& game);


	/*
	  The method return all the game from repo
	  Input:-
	  Outpud:-a constant reference to an array of games
	*/
	const vector < Game >& get_all();

	~Game_Repo() = default;

};


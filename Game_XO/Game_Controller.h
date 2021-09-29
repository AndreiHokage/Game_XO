#pragma once
#include <string>
#include <vector>
#include <qdebug.h>
#include <fstream>
#include <utility>
#include <assert.h>
#include "Game.h"
#include "Exceptions.h"
#include "Game_Repo.h"
#include "Validator.h"
#include "Observer.h"
using std::string;
using std::vector;
using std::pair;

class Game_Controller:public Observable 
{

private:
	Game_Repo& repo;
	Validator& vad;
	pair < char, int > win_map;

public:
	Game_Controller() = delete;

	Game_Controller(Game_Repo& repo, Validator& vad) :repo{ repo }, vad{ vad } {

	}

	Game_Controller(const Game_Controller&) = delete;

	/*
	* The method add a new game
	* Input:id-an id for game(integer type)
	*		dim-the size of the game board(dimxdim) (integer type)
	*		table-board of the game
	*		player-current player
	*		state-status of the game
	* Output:A new game is added and it s returned
	* Throw exception if the game already exists or the game is invalid
	*/
	Game add_game(int id, int dim, const string& table, const string& player, const string& state);

	/*
	* The method update a game
	* Input:id-an id for game(integer type)
	*		dim-the size of the new game board(dimxdim) (integer type)
	*		table-board of the new  game
	*		player-current new  player
	*		state-status of the new  game
	* Output:Return the previous game before updating
	* Throw exception if the game doesn't exists or the game is invalid
	*/
	Game update_game(int id, int dim, const string& table, const string& player, const string& state);

	/*
	* Update the game after the character on the position index was modified
	* Input:game-a Game
	*		index-position on the board game where the character was modified
	* Output:the previos game
	*/
	Game update_game_after_play(Game& game,int index);

	/*
	* The method check if the current player won the game and mark in 'win_map' if the winning was on row,column,or diagonal
	* and the number of row,column,{1-for main diagonal,-1 for the another one diagonal}
	* Input:dim-size of board game
	*		table-board game
	* Output:true-if the game was won by current player
	*		 false-otherwise
	*/
	bool is_game_win(int dim,const string& table);

	/*
	* Return the case of winnig
	*/
	pair<char, int> get_win_map();

	/*
	* Return all the games
	*/
	const vector < Game >& get_all();

	/*
	Sort all games after their status
	*/
	vector < Game > sorted_status() const;
};


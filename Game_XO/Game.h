#pragma once
#include <string>
#include <iostream>
using std::string;
using std::ostream;

class Game
{

private:
	int id;
	int dim;
	string table;
	string player;
	string state;

public:

	Game() = default;

	Game(int id,int dim, const string& table, const string& player, const string& state) :id{ id },dim{ dim }, table{ table }, player{ player }, state{ state }{
	}

	Game(const Game& game) = default;

	Game& operator=(const Game& game)=default;

	Game(Game&& game) = default;

	Game& operator=(Game&& ot) = default;

	//getter method
	int get_id() const {
		return id;
	}

	//getter method
	int get_dim() const {
		return dim;
	}

	//getter method
	string get_table() const {
		return table;
	}

	string get_player() const {
		return player;
	}

	//getter method
	string get_state() const {
		return state;
	}

	//setter method
	void set_dim(int dim) {
		this->dim = dim;
	}

	//setter method
	void set_table(string table) {
		this->table = table;
	}

	//setter method
	void set_player(string player) {
		this->player = player;
	}

	//setter method
	void set_state(string state) {
		this->state = state;
	}

	bool operator==(const Game& game) const noexcept;

	friend ostream& operator<<(ostream& os, const Game& game);

	~Game() = default;


};


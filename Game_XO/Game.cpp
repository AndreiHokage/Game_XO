#include "Game.h"

bool Game::operator==(const Game& game) const noexcept {
	return this->id == game.id;
}

/*Game& Game::operator=(const Game& game) { //It's doesn't want to change the id
	this->dim = game.dim;
	this->player = game.player;
	this->table = game.table;
	this->state = game.state;

	return *this;
}*/

ostream& operator<<(ostream& os, const Game& game) {
	os << "Id: " << game.id << " Dim: " << game.dim << " Table: " << game.table << " Player: " << game.player << " State: " << game.state;
	return os;
}
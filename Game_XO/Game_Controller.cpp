#include "Game_Controller.h"

Game Game_Controller::add_game(int id, int dim, const string& table, const string& player, const string& state) {
	Game game{ id,dim,table,player,state };
	vad.start_validate(game);
	return repo.add_game(game);
}

Game Game_Controller::update_game(int id, int dim, const string& table, const string& player, const string& state) {
	Game game{ id,dim,table,player,state };
	vad.validate(game);
	return repo.update_game(game);
}

Game Game_Controller::update_game_after_play(Game& game, int index) {
	string S = game.get_table();
	if (game.get_player() == "X") {
		S[index] = 'X';
		game.set_player("O");
	}
	else {
		S[index] = 'O';
		game.set_player("X");
	}
	game.set_table(S);

	int ch_xo = 0, ch_space = 0;
	for (char c : S)
		if (c != '-') ch_xo++;
		else ch_space++;

	if ((ch_space == 0 && ch_xo == game.get_dim() * game.get_dim()) || is_game_win(game.get_dim(), game.get_table()))
		game.set_state("Terminat");
	else
		if (ch_space && ch_xo < game.get_dim() * game.get_dim())
			game.set_state("In derulare");

	Game prev_game=repo.update_game(game);
	notify();

	return prev_game;
}

bool Game_Controller::is_game_win(int dim,const string& table) {
	vector < vector < char > > v(dim, vector < char > (dim));
	for (int i = 0; i < table.size(); i++) v[i / dim][i % dim] = table[i];

	for (int i = 0; i < dim; i++) {
		bool win = true;
		for (int j = 0; j < dim; j++)
			if (v[i][0] != '-' && v[i][j] == v[i][0])
				continue;
			else {
				win = false;
				break;
			}
		if (win) {
			win_map = { 'R',i };
			return true;
		}
	}

	for (int j = 0; j < dim; j++) {
		bool win = true;
		for (int i = 0; i < dim; i++)
			if (v[0][j] != '-' && v[i][j] == v[0][j])
				continue;
			else {
				win = false;
				break;
			}
		if (win) {
			win_map = { 'C',j };
			return true;
		}
	}

	bool win = true;
	for (int i = 0; i < dim; i++)
		if (v[0][0] != '-' && v[i][i] == v[0][0])
			continue;
		else {
			win = false;
			break;
		}

	if (win)
	{
		win_map = { 'D',1 };
		return true;
	}

	win = true;
	for (int i = 0; i < dim; i++)
		if (v[0][dim-1] != '-' && v[i][dim-i-1] == v[0][dim-1])
			continue;
		else {
			win = false;
			break;
		}

	if (win) {
		win_map = { 'D',-1 };
		return true;
	}

	win_map = { 'N',-1 };
	return false;
}

pair<char, int> Game_Controller::get_win_map() {
	return win_map;
}

const vector < Game >& Game_Controller::get_all() {
	return repo.get_all();
}

vector < Game > Game_Controller::sorted_status() const {
	vector < Game > v = repo.get_all();
	sort(v.begin(), v.end(), [&](const Game& x, const Game& y) {
		if (x.get_state() == y.get_state())
			return x.get_id() < y.get_id();
		return x.get_state() < y.get_state();
		});
	return v; //it s called copy constructor ot move constructor
}
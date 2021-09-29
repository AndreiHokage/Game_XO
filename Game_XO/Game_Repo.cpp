#include "Game_Repo.h"


vector < string > Game_Repo::split_string(string S) {
	vector < string > v;
	
	int start = 0;
	int end = S.find(';');
	while (end != -1) {
		string aux = S.substr(start, end - start);
		v.push_back(aux);
		start = end + 1;
		end = S.find(';', start);
	}
	v.push_back(S.substr(start, end - start));
	return v;
}

void Game_Repo::loadfromfile() {
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		throw FileError{ "The file cannot be open!\n" };
	}

	while (!fin.eof()) {
		string S;
		getline(fin, S);

		if (S == "")
			continue;

		vector < string > v = split_string(S);
		int id = stoi(v[0]);
		int dim = stoi(v[1]);
		string table = v[2];
		string player = v[3];
		string state = v[4];

		repo.push_back(Game{ id,dim,table,player,state });
	}
	fin.close();
}

void Game_Repo::storetofile() {
	std::ofstream fout(filename, std::ios::trunc);
	if (!fout.is_open()) {
		throw FileError("The file cannot be open!\n");
	}

	for (const Game& game : repo) //to avoid making copies
	{
		fout << game.get_id()<<';'<<game.get_dim() << ';' << game.get_table() << ";" << game.get_player() << ';' << game.get_state() << '\n';
	}
	fout.close();
}

Game Game_Repo::add_game(const Game& game) {
	
	for (const Game& obj : repo)
		if (obj == game)
			throw RepoError("The game exists!\n");

	repo.push_back(game);
	storetofile();

	return game;
}

Game Game_Repo::update_game(const Game& game) {
	for(Game& obj:repo) //I want to take a reference of an element,I don't want a copy of an element(Game& ...)
		if (obj== game)
		{
			Game prev_game = obj;//it's called copy constructor of Game class!It's making a copy
			obj = game;
			storetofile();

			return prev_game; //I can t return through reference because of prev_game is a variable declared on stack
		}
	throw RepoError("There isn't any game to update!\n");
}

const vector < Game >&  Game_Repo::get_all() {
	return repo;
}
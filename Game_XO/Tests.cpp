#include "Tests.h"


void Tests::run_tests() {
	run_domain_game();
	run_validate_game();
	run_repo_game();
	run_add_repo_game();
	run_update_repo_game();
	run_add_controller();
	run_update_controller();
	run_sorted_status();
	run_update_after_play();
	run_is_win_game();
}

void Tests::run_domain_game() {
	Game game{0,3,"---XXXO-X","X","Terminat" };
	assert(game.get_id() == 0);
	assert(game.get_dim() == 3);
	assert(game.get_player() == "X");
	assert(game.get_state() == "Terminat");
	assert(game.get_table() == "---XXXO-X");

	std::stringstream sout;
	sout << game;
	string mesaj = sout.str();
	assert(mesaj == "Id: 0 Dim: 3 Table: ---XXXO-X Player: X State: Terminat");

	game.set_dim(4);
	game.set_table("XXXXXXXXOXXXXXXX");
	game.set_player("O");
	game.set_state("Neinceput");

	assert(game.get_dim() == 4);
	assert(game.get_player() == "O");
	assert(game.get_state() == "Neinceput");
	assert(game.get_table() == "XXXXXXXXOXXXXXXX");

	Game game1{1,1,"X","X","In derulare" };
	assert(game1.get_id() == 1);
	assert(!(game1 == game));

}

void Tests::run_validate_game() {

	Validator vad;

	Game game{ 1,2,"X-OP","S","LALALA" };
	try {
		vad.validate(game);
	}
	catch (const GameError& e) {
		assert(e.get_msg() == "Invalid dimension of table!\nInvalid table game!\nInvalid player!\nInvalid state of game!\n");
	}

	Game oth_game{ 1,3,"XXXOO----","O","LALA" };
	try {
		vad.start_validate(oth_game);
	}
	catch (const GameError& e) {
		assert(e.get_msg() == "For a new game,the status has to be Neinceput!\n");
	}

	oth_game.set_state("Started");
	try {
		vad.start_validate(oth_game);
	}
	catch (const GameError& e) {
		assert(true);
	}
}

void Tests::run_repo_game() {
	std::ofstream g(filename, std::ios::trunc);
	g << "0;3;XXOOOXXXO;X;Inceput\n";
	g << "1;4;XXXXOOOOXXXXOOXX;O;Terminat\n";
	g << "2;1;X;O;In derulare\n";
	g.close();

	Game_Repo repo{ filename };
	const vector < Game >& rez = repo.get_all();
	assert(rez.size() == 3);
	assert(rez[0].get_table() == "XXOOOXXXO");
	assert(rez[1].get_dim() == 4);
	assert(rez[2].get_state() == "In derulare");
}

void Tests::run_add_repo_game() {
	std::ofstream g(filename, std::ios::trunc);
	g.close();

	Game_Repo repo{ filename };
	repo.add_game(Game{1,5,"----","O","La incepu" });
	const vector < Game >& rez = repo.get_all();
	assert(rez.size() == 1);
	assert(rez[0].get_player() == "O");

	try {
		repo.add_game(Game{ 1,5,"-","O","dfs" });
	}
	catch (const RepoError& e) {
		assert(e.get_msg() == "The game exists!\n");
	}
}

void Tests::run_update_repo_game() {
	std::ofstream g(filename, std::ios::trunc);
	g << "0;3;XXOOOXXXO;X;Inceput\n";
	g << "1;4;XXXXOOOOXXXXOOXX;O;Terminat\n";
	g << "2;1;X;O;In derulare\n";
	g.close();

	Game_Repo repo{ filename };
	Game game=repo.update_game(Game{ 1,5,"OO","X","In derulare" });
	assert(game.get_id() == 1);
	const vector < Game >& rez = repo.get_all();
	assert(rez[1].get_table() == "OO");
	assert(rez[1].get_player() == "X");

	try {
		repo.update_game(Game{ 6,5,"-","O","dfs" });
	}
	catch (const RepoError& e) {
		assert(e.get_msg() == "There isn't any game to update!\n");
	}

}

void Tests::run_add_controller() {
	std::ofstream g(filename, std::ios::trunc);
	g << "0;3;XXO---XXX;X;Started\n";
	g << "1;4;XXXXOOOOXXXXOOXX;O;Finished\n";
	g.close();

	Validator vad{};
	Game_Repo repo{ filename };
	Game_Controller srv{ repo,vad };

	srv.add_game(3, 3, "------XOX", "O", "Started");
	const vector < Game >& rez = srv.get_all();
	assert(rez.size() == 3);
	assert(rez[2].get_id() == 3);
}

void Tests::run_update_controller() {
	std::ofstream g(filename, std::ios::trunc);
	g << "0;3;XXO---XXX;X;Started\n";
	g << "1;4;XXXXOOOOXXXXOOXX;O;Finished\n";
	g.close();

	Validator vad{};
	Game_Repo repo{ filename };
	Game_Controller srv{ repo,vad };

	srv.update_game(0, 3, "XXOX--XXX", "O", "Playing");
	const vector < Game >& rez = srv.get_all();
	assert(rez.size() == 2);
	assert(rez[0].get_table() == "XXOX--XXX");
}

void Tests::run_sorted_status() {
	std::ofstream g(filename, std::ios::trunc);
	g << "1;4;XXXXOOOOXXXXOOXX;O;Finished\n";
	g << "0;3;XXO---XXX;X;Started\n";
	g << "2;3;XXO---XXX;X;Playing\n";
	g.close();

	Validator vad{};
	Game_Repo repo{ filename };
	Game_Controller srv{ repo,vad };
	vector < Game > rez = srv.sorted_status();
	assert(rez[0].get_id() == 1);
	assert(rez[1].get_id() == 2);
	assert(rez[2].get_id() == 0);
}

void Tests::run_update_after_play() {
	std::ofstream g(filename, std::ios::trunc);
	g << "1;4;XXXXOOOOXXXXOOXX;O;Finished\n";
	g << "0;3;OOX---OXO;X;Started\n";
	g << "2;3;XXO---XOX;X;Playing\n";
	g.close();

	Validator vad{};
	Game_Repo repo{ filename };
	Game_Controller srv{ repo,vad };

	const vector < Game >& rez = srv.get_all();
	Game game = rez[1];
	srv.update_game_after_play(game, 3);
	assert(game.get_player() == "O");
	
	assert(game.get_table() == "OOXX--OXO");
	assert(game.get_state() == "Playing");

	srv.update_game_after_play(game, 4);
	srv.update_game_after_play(game, 5);

	assert(game.get_player() == "O");
	assert(game.get_table() == "OOXXOXOXO");
	assert(game.get_state() == "Finished");
}

void Tests::run_is_win_game() {
	Validator vad{};
	Game_Repo repo{ filename };
	Game_Controller srv{ repo,vad };
	bool win = srv.is_game_win(3, "XXX------");
	assert(win == true);
	assert(srv.get_win_map().first == 'R');
	assert(srv.get_win_map().second == 0);

	win = srv.is_game_win(4, "X---X---X---X---");
	assert(win == true);
	assert(srv.get_win_map().first == 'C');
	assert(srv.get_win_map().second == 0);

	win = srv.is_game_win(5, "O-----O-----O-----O-----O");
	assert(win == true);
	assert(srv.get_win_map().first == 'D');
	assert(srv.get_win_map().second == 1);

	win = srv.is_game_win(5, "----O---O---O---O---O----");
	assert(win == true);
	assert(srv.get_win_map().first == 'D');
	assert(srv.get_win_map().second == -1);

	win = srv.is_game_win(3, "---------");
	assert(win == false);
	assert(srv.get_win_map().first == 'N');
	assert(srv.get_win_map().second == -1);
}
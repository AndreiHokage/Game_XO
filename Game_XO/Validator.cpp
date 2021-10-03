#include "Validator.h"

void Validator::validate(const Game& game) {

	string errors = "";

	if (!(game.get_dim() >= 3 && game.get_dim() <= 5))
		errors += "Invalid dimension of table!\n";
	
	bool ok = true;
	if (game.get_table().size() != game.get_dim() * game.get_dim()) ok = false;

	for (char x : game.get_table()) {
		if (x == 'X' || x == 'O' || x == '-')
			continue;
		else
		{
			ok = false;
			break;
		}
	}
	if (!ok) errors += "Invalid table game!\n";

	if (!(game.get_player() == "X" || game.get_player() == "O"))
		errors += "Invalid player!\n";

	ok = false;
	for (const string& x : enum_state)
		if (game.get_state() == x)
		{
			ok = true;
			break;
		}

	if (!ok) errors += "Invalid state of game!\n";

	if (errors != "")
		throw GameError{ errors };

}

void Validator::start_validate(const Game& game) {
	if (game.get_state() != "Started")
		throw GameError{ "For a new game,the status has to be Neinceput!\n" };
	validate(game);
}
#pragma once
#include <string>
#include <vector>
#include <qdebug.h>
#include <fstream>
#include <assert.h>
#include "Game.h"
#include "Exceptions.h"
#include "Game_Repo.h"
#include "Validator.h"
#include "Game_Controller.h"
using std::string;
using std::vector;

class Tests
{

public:
	Tests(const string& filename) :filename{ filename } {

	}

	void run_tests();

private:

	string filename;

	void run_domain_game();
	void run_validate_game();
	void run_repo_game();
	void run_add_repo_game();
	void run_update_repo_game();
	void run_add_controller();
	void run_update_controller();
	void run_sorted_status();
	void run_update_after_play();
	void run_is_win_game();

};


#pragma once
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <qsignalmapper.h>
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
#include "Observer.h"
using std::string;
using std::vector;

class MyTableModel;

class Game_TableXO :public QWidget
{
private:

	Game_Controller& srv;
	Game game;
	vector < vector < QPushButton* > > v;
	vector < QHBoxLayout* > ly_button;

	QVBoxLayout* lymain = new QVBoxLayout();


	void clear_table();
	void build_table();
	void init_GUI();
	void push_buttonxo(int,int);

public:

	Game_TableXO(Game_Controller& srv) :srv{ srv } {


		for (int i = 0; i < 5; i++)
		{
			ly_button.push_back(new QHBoxLayout);
			lymain->addLayout(ly_button.back());
		}
	}

	/*
	* Update the board game:
	*		-clean the board game
	*		-build the board game
	*		-draw the gui components
	*/
	void update_gametablexo(const Game& game);

	/*
	* Color the row,column or oane o the diagonal for that the game is won
	*/
	void color_thewinner();

	~Game_TableXO() {
	
	}

};

class Game_UI:public QWidget, public Observer
{

private:
	Game_Controller& srv;

	QHBoxLayout* lymain = new QHBoxLayout();
	QTableView* tbl;
	MyTableModel* model;
	QLineEdit* txt_id, * txt_dim, * txt_table, * txt_player, * txt_status;
	QPushButton* btn_add, * btn_update;
	Game_TableXO* game_tablexo;

	void initGUI();
	void connect();
	void cleanedit();
	void add_game();
	void update_game();
	void reload(const vector < Game >&);

	/*
	* Reload again the list with all games
	* If one game is already won,the the board game is colores
	*/
	void update() override;

public:
	Game_UI(Game_Controller& srv) :srv{ srv } {
		game_tablexo = new Game_TableXO(srv);
		initGUI();
		connect();
	}

	Game_UI(const Game_UI&) = delete;

	~Game_UI() {
		srv.detachsubsriber(this);
	}

};

class MyTableModel :public QAbstractTableModel
{
private:
	vector < Game > v;
public:
	MyTableModel(const vector < Game >& v) :v{ v } {

	}

	void reload_tablemodel(const vector < Game >& rez);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return v.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& parent, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

};

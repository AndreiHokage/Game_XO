#include "Game_UI.h"

QVariant MyTableModel::data(const QModelIndex& index, int role) const {

	if (role == Qt::DisplayRole) {
		const Game& game = v[index.row()];
		if (index.column() == 0)
			return QString::number(game.get_id());
		else
			if (index.column() == 1)
				return QString::number(game.get_dim());
			else
				if (index.column() == 2)
					return QString::fromStdString(game.get_table());
				else
					if (index.column() == 3)
						return QString::fromStdString(game.get_player());
					else
						if (index.column() == 4)
							return QString::fromStdString(game.get_state());
	}

	return QVariant{};
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0)
				return "Id";
			if (section == 1)
				return "Dim of table game";
			if (section == 2)
				return "Game table";
			if (section == 3)
				return "Current player";
			if (section == 4)
				return "Status game";
		}
	}

	return QVariant();
}

void Game_UI::initGUI() {
	setLayout(lymain);
	model = new MyTableModel(srv.sorted_status());
	tbl = new QTableView();
	tbl->setModel(model);

	QVBoxLayout* left = new QVBoxLayout();
	left->addWidget(tbl);

	lymain->addLayout(left);

	QVBoxLayout* right = new QVBoxLayout();
	txt_id = new QLineEdit;
	txt_dim = new QLineEdit;
	txt_player = new QLineEdit;
	txt_table = new QLineEdit;
	txt_status = new QLineEdit;

	QFormLayout* form = new QFormLayout();
	form->addRow("ID: ", txt_id);
	form->addRow("Dim: ", txt_dim);
	form->addRow("Game table: ", txt_table);
	form->addRow("Current player: ", txt_player);
	form->addRow("Status game: ", txt_status);
	right->addLayout(form);

	QHBoxLayout* ly_buttons = new QHBoxLayout;
	btn_add = new QPushButton("Add a new game");
	btn_update = new QPushButton("Update an existent game");
	ly_buttons->addWidget(btn_add);
	ly_buttons->addWidget(btn_update);
	right->addLayout(ly_buttons);

	lymain->addLayout(right);

}

void Game_UI::connect() {
	srv.addsubsriber(this);
	QObject::connect(btn_add, &QPushButton::clicked, this, &Game_UI::add_game);
	QObject::connect(btn_update, &QPushButton::clicked, this, &Game_UI::update_game);
	QObject::connect(tbl->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tbl->selectionModel()->selectedIndexes().isEmpty()) {
			game_tablexo->hide();
			return;
		}

		int row = tbl->selectionModel()->selectedIndexes().at(0).row();
		const vector < Game >& rez = srv.sorted_status();
		game_tablexo->update_gametablexo(rez[row]);
		game_tablexo->show();
		});
}

void Game_UI::cleanedit() {
	txt_id->clear();
	txt_dim->clear();
	txt_table->clear();
	txt_player->clear();
	txt_status->clear();
}

void Game_UI::add_game() {
	bool ok;
	int id = txt_id->text().toInt(&ok);
	if (ok == false) {
		QMessageBox::warning(this, "Warning", "Invalid data:ID has to be integer!");
		cleanedit();
		return;
	}

	int dim = txt_dim->text().toInt(&ok);
	if (ok == false) {
		QMessageBox::warning(this, "Warning", "Invalid data:The size of game table has to be integer!");
		cleanedit();
		return;
	}

	string table = txt_table->text().toStdString();
	string player = txt_player->text().toStdString();
	string status = txt_status->text().toStdString();

	try {
		srv.add_game(id, dim, table, player, status);
		reload(srv.sorted_status());
	}
	catch (const GameError& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	catch (const RepoError& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
}

void Game_UI::update_game() {
	bool ok;
	int id = txt_id->text().toInt(&ok);
	if (ok == false) {
		QMessageBox::warning(this, "Warning", "Invalid data:ID has to be integer!");
		cleanedit();
		return;
	}

	int dim = txt_dim->text().toInt(&ok);
	if (ok == false) {
		QMessageBox::warning(this, "Warning", "Invalid data:The size of game table has to be integer!");
		cleanedit();
		return;
	}

	string table = txt_table->text().toStdString();
	string player = txt_player->text().toStdString();
	string status = txt_status->text().toStdString();

	try {
		srv.update_game(id, dim, table, player, status);
		reload(srv.sorted_status());
	}
	catch (const GameError& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
	catch (const RepoError& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
	}
}

void Game_UI::reload(const vector< Game >& v) {
	model->reload_tablemodel(v);
}

void MyTableModel::reload_tablemodel(const vector < Game >& rez) {
	v = rez;
	emit layoutChanged();
}

void Game_TableXO::clear_table() {

	if (!v.size())
		return;

	int dim = game.get_dim();
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			ly_button[i]->removeWidget(v[i][j]);
			delete v[i][j];
		}
		v[i].clear();
	}
}

void Game_TableXO::build_table() {

	string table_game = game.get_table();
	int dim = game.get_dim();

	v=vector < vector < QPushButton* > >(dim, vector < QPushButton* >(dim));
	for (int i = 0; i < table_game.size(); i++) {
		int line = i / dim;
		int column = i % dim;
		v[line][column] = new QPushButton(QChar(table_game[i]));
		QObject::connect(v[line][column], &QPushButton::clicked, this, [this, line,column] { push_buttonxo(line,column); });
	}
}

void Game_TableXO::push_buttonxo(int x,int y) {
	QPushButton* btn = v[x][y];

	if (btn->text() != "-" || game.get_state() == "Terminat")
		return;
	btn->setText(QString::fromStdString(game.get_player()));
	
	srv.update_game_after_play(game, game.get_dim() * x + y);

}

void Game_TableXO::init_GUI() {
	setLayout(lymain);
	for (int i = 0; i < game.get_dim(); i++) {
		for (int j = 0; j < game.get_dim(); j++) {
			ly_button[i]->addWidget(v[i][j]);
		}
	}
}

void Game_TableXO::update_gametablexo(const Game& game) {
	clear_table();
	this->game = game;
	build_table();
	init_GUI();
}

void Game_TableXO::color_thewinner() {
	pair<char, int> win_map = srv.get_win_map();
	char letter = win_map.first;
	int digit = win_map.second;

	if (letter == 'R') {
		for (int j = 0; j < game.get_dim(); j++)
			v[digit][j]->setStyleSheet("background-color: red");
	}

	if (letter == 'C') {
		for (int i = 0; i < game.get_dim(); i++)
			v[i][digit]->setStyleSheet("background-color: red");
	}

	if (letter == 'D' && digit == 1) {
		for (int i = 0; i < game.get_dim(); i++)
			v[i][i]->setStyleSheet("background-color: red");
	}

	if (letter == 'D' && digit == -1) {
		for (int i = 0; i < game.get_dim(); i++)
			v[i][game.get_dim()-i-1]->setStyleSheet("background-color: red");
	}
}

void Game_UI::update() {
	reload(srv.sorted_status());
	if (srv.get_win_map().first != 'N')
		game_tablexo->color_thewinner();
}
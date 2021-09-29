#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Game_XO.h"

class Game_XO : public QMainWindow
{
    Q_OBJECT

public:
    Game_XO(QWidget *parent = Q_NULLPTR);

private:
    Ui::Game_XOClass ui;
};

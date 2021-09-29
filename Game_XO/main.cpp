#include "Game_XO.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include "Game_Repo.h"
#include "Game_Controller.h"
#include "Validator.h"
#include "Game_UI.h"

int main(int argc, char *argv[])
{
    {
        QApplication a(argc, argv);

        Tests tests{ "game_test.txt" };
        tests.run_tests();

        Validator vad{};
        Game_Repo repo{ "game.txt" };
        Game_Controller srv{ repo,vad };
        Game_UI console{ srv };

        console.show();

        a.exec();
    }
    return 0;
}

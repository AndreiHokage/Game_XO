# Game_XO
I have created this XO game to prove my skills in object oriented programming.I have used Layer Architecture to create my game and Observer pattern,Model-View-Controller pattern.
In order to make the GUI ,I used QT C++.I have tried to use all my knowdledges from my OOP lectures and Software Enginnering lectures.

The statement of the problem:
Make a C++ app which implements TicTacToe game.The app manages more games,a game has an id,dim(dimension of the board),a game board(For dim=3,a string of 9 character from the set={'X','O','-'},player-current player and status of game(Started,Playing,Finished).The games are saved in a file(Example of a line file:1 3 X-OXO-XOO X Finished).Features:
    1)At the beginning of app,it shows a table(QTableView) with all games.
    2)Add a new game.
    3)The user can update  a game.
    4)When select a game from the table,the app creates the board of game with dim*dim cells.
    5)The app allows to pay tictactoe game.

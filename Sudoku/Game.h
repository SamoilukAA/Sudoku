#pragma once
#include <SFML/Graphics.hpp>
#include "SudokuField.h"
#include <string>
#include <fstream>
#include <Windows.h>
using namespace sf;

class Game {
private:
	const int fsize = 9, cellSize = 60;
	sudokuF field, tmp;
	bool bl[9][9];
	RenderWindow window;

	void drawSquare(RenderWindow& window1);
	void game();
	void helpF();
	void settingsF();
	void newGame(string level);
	void saveGame();
	void winMenu();
	void chosenCell(RenderWindow& window1);
	void chooseLevelMenu();
	void rules();
	bool loadGame();

public:
	Game();
	void menu();
};
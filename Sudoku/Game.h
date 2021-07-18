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

	void drawSquare(RenderWindow& window1)
	{
		int quad = 3;
		int fontSize = 30;

		Font font;
		font.loadFromFile("../book_antiqua.ttf");

		RectangleShape mediumSquare;
		mediumSquare.setSize(Vector2f(cellSize * quad, cellSize * quad));
		mediumSquare.setOutlineThickness(2);
		mediumSquare.setOutlineColor(Color::Black);
		mediumSquare.setFillColor(Color::Transparent);

		RectangleShape bigSquare;
		bigSquare.setSize(Vector2f(cellSize * fsize, cellSize * fsize));
		bigSquare.setOutlineThickness(4);
		bigSquare.setOutlineColor(Color::Black);
		bigSquare.setFillColor(Color::Transparent);
		bigSquare.setPosition((300 - fsize / 2 * cellSize), (300 - fsize / 2 * cellSize));

		RectangleShape smallSquare;
		smallSquare.setSize(Vector2f(cellSize, cellSize));
		smallSquare.setOutlineThickness(1);
		smallSquare.setOutlineColor(Color(200, 200, 200));
		smallSquare.setFillColor(Color::White);

		for (int i = 0; i < fsize; i++)
		{
			for (int j = 0; j < fsize; j++)
			{
				smallSquare.setPosition((300 - fsize / 2 * cellSize) + j * cellSize, (300 - fsize / 2 * cellSize) + i * cellSize);
				window1.draw(smallSquare);
				string text;
				if (tmp.getCell(i, j) > 0)
				{
					text = to_string(tmp.getCell(i, j));
				}
				else
				{
					text = "";
				}
				Text cell(text, font, fontSize);
				cell.setPosition((300 - fsize / 2 * cellSize) + j * cellSize + fontSize / 1.3, (300 - fsize / 2 * cellSize) + i * cellSize + fontSize / 2.3);
				cell.setFillColor(Color::Black);
				if (bl[i][j])
				{
					cell.setFillColor(Color(114, 167, 240));
				}
				window1.draw(cell);
			}
		}

		for (int i = 0; i < fsize; i++)
		{
			for (int j = 0; j < fsize; j++)
			{
				if (i % quad == 0 && j % quad == 0)
				{
					mediumSquare.setPosition((300 - fsize / 2 * cellSize) + j * cellSize, (300 - fsize / 2 * cellSize) + i * cellSize);
					window1.draw(mediumSquare);
				}
			}
		}
		window1.draw(bigSquare);
	}

	void game() {
		window.create(VideoMode(750, 700), "Sudoku");
		Texture gameBackground, settingButton, helpButton;
		gameBackground.loadFromFile("../images/game.jpg");
		settingButton.loadFromFile("../images/settings.png");
		helpButton.loadFromFile("../images/help.png");
		Sprite gameBg(gameBackground), settings(settingButton), help(helpButton);
		Vector2f targetSize(800, 700), sizeS(40, 40), sizeH(40, 40);
		gameBg.setScale(targetSize.x / gameBg.getLocalBounds().width, targetSize.y / gameBg.getLocalBounds().height);
		settings.setScale(sizeS.x / settings.getLocalBounds().width, sizeS.y / settings.getLocalBounds().height);
		help.setScale(sizeH.x / help.getLocalBounds().width, sizeH.y / help.getLocalBounds().height);
		gameBg.setPosition(0, 0);
		settings.setPosition(660, 55);
		help.setPosition(660, 540);
		Font font;
		font.loadFromFile("../book_antiqua.ttf");
		Text hl("Help", font, 20);
		hl.setPosition(660, 580);
		hl.setFillColor(Color::Black);
		bool isGame = true;
		int buttonNum = 0;
		while (isGame && window.isOpen()) {
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window.close();
				}
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && buttonNum == 2) {
					tmp.openCell(field);
					winMenu();
				}
			}
			window.draw(gameBg);
			window.draw(settings);
			window.draw(help);
			window.draw(hl);
			drawSquare(window);
			buttonNum = 0;
			settings.setColor(Color::White);
			if (IntRect(660, 55, 40, 40).contains(Mouse::getPosition(window))) {
				settings.setColor(Color(114, 167, 240));
				buttonNum = 1;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && buttonNum == 1) {
				settingsF();
			}
			help.setColor(Color::White);
			if (IntRect(660, 540, 40, 40).contains(Mouse::getPosition(window))) {
				help.setColor(Color(114, 167, 240));
				buttonNum = 2;
			}
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i coord = Mouse::getPosition(window);
				int i0 = 300 - fsize / 2 * cellSize, i1 = (300 - fsize / 2 * cellSize) + 9 * cellSize;
				int i = (coord.y - (300 - fsize / 2 * cellSize)) / cellSize, j = (coord.x - (300 - fsize / 2 * cellSize)) / cellSize;
				if (coord.x >= i0 && coord.x <= i1 && coord.y >= i0 && coord.y <= i1 && tmp.getCell(i, j) == 0)
					chosenCell(window);
			}
			window.display();
		}
	}

	void helpF() {
		srand(time(0));
		int i, j;
		bool chosen = false;
		while (!chosen) {
			i = rand() % fsize;
			j = rand() % fsize;
			if (tmp.getCell(i, j) == 0) {
				tmp.setCell(i, j, field.getCell(i, j));
				chosen = true;
			}

		}
	}

	void settingsF() {
		RenderWindow window1(VideoMode(500, 500), "Settings");
		Texture settingsBackground, backButton;
		settingsBackground.loadFromFile("../images/game.jpg");
		backButton.loadFromFile("../images/back.png");
		Sprite settingsBg(settingsBackground), bk(backButton);
		Vector2f targetSize(500, 500), targetSize2(40, 40);
		settingsBg.setScale(targetSize.x / settingsBg.getLocalBounds().width, targetSize.y / settingsBg.getLocalBounds().height);
		bk.setScale(targetSize2.x / bk.getLocalBounds().width, targetSize2.y / bk.getLocalBounds().height);
		settingsBg.setPosition(0, 0);
		bk.setPosition(50, 430);
		Font font;
		font.loadFromFile("../book_antiqua.ttf");
		Text t0("Settings", font, 45), t1("New game", font, 30), t2("Save game", font, 30), t3("Rules", font, 30), t4("Quit without saving", font, 30);
		t0.setPosition(170, 35);
		t1.setPosition(100, 120);
		t2.setPosition(100, 190);
		t3.setPosition(100, 260);
		t4.setPosition(100, 330);
		bool isSettings = true, back = false;
		int menuNum;
		while (isSettings && window1.isOpen()) {
			Event event;
			while (window1.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window1.close();
				}
			}
			t0.setFillColor(Color::Black);
			t1.setFillColor(Color::Black);
			t2.setFillColor(Color::Black);
			t3.setFillColor(Color::Black);
			t4.setFillColor(Color::Black);
			menuNum = 0;
			if (IntRect(100, 120, 150, 40).contains(Mouse::getPosition(window1))) {
				t1.setFillColor(Color(114, 167, 240));
				menuNum = 1;
			}
			if (IntRect(100, 190, 150, 40).contains(Mouse::getPosition(window1))) {
				t2.setFillColor(Color(114, 167, 240));
				menuNum = 2;
			}
			if (IntRect(100, 260, 70, 40).contains(Mouse::getPosition(window1))) {
				t3.setFillColor(Color(114, 167, 240));
				menuNum = 3;
			}
			if (IntRect(100, 330, 270, 40).contains(Mouse::getPosition(window1))) {
				t4.setFillColor(Color(114, 167, 240));
				menuNum = 4;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && menuNum == 1) {
				isSettings = false;
				window1.close();
				window.close();
				chooseLevelMenu();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && menuNum == 2) {
				saveGame();
				MessageBox(NULL, L"The game is saved", L"Save game", MB_OK);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && menuNum == 3) {
				rules();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && menuNum == 4) {
				exit(0);
			}
			bk.setColor(Color::White);
			if (IntRect(50, 430, 45, 45).contains(Mouse::getPosition(window1))) {
				bk.setColor(Color(114, 167, 240));
				back = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && back == true) {
				isSettings = false;
				window1.close();
			}
			window1.draw(settingsBg);
			window1.draw(t0);
			window1.draw(t1);
			window1.draw(t2);
			window1.draw(t3);
			window1.draw(t4);
			window1.draw(bk);
			window1.display();
		}
	}

	void newGame(string level) {
		field = createFull();
		tmp = field;
		tmp.createSudoku(level);
		for (int i = 0; i < fsize; i++)
			for (int j = 0; j < fsize; j++)
				bl[i][j] = false;
	}

	void saveGame() {
		remove("savedGame.txt");
		ofstream fOut("savedGame.txt");
		if (fOut.is_open()) {
			//fOut.trunc;
			for (int i = 0; i < fsize; i++)
				for (int j = 0; j < fsize; j++)
					fOut << field.getCell(i, j) << " ";
			fOut << endl;
			for (int i = 0; i < fsize; i++)
				for (int j = 0; j < fsize; j++)
					fOut << tmp.getCell(i, j) << " ";
			fOut << endl;
			for (int i = 0; i < fsize; i++)
				for (int j = 0; j < fsize; j++) {
					if (bl[i][j])
						fOut << 1 << " ";
					else
						fOut << 0 << " ";
				}
			fOut.close();
		}
		else {
			MessageBox(NULL, L"Fail to save the game :(", L"Error!", MB_OK);
		}
	}

	void winMenu() {
		if (tmp.checkWin()) {
			remove("savedGame.txt");
			/*ofstream fOut("savedGame.txt");
			fOut.trunc;
			fOut.close();*/
			int message = MessageBox(NULL, L"You win!\nStart a new game?", L"Victory", MB_YESNO);
			if (message == IDYES) {
				window.close();
				chooseLevelMenu();
			}
			else
				if (message == IDNO)
					exit(0);
		}
	}

	void chosenCell(RenderWindow& window1) {
		bool isChosen = true;
		Vector2i coord = Mouse::getPosition(window1);
		RectangleShape smallSquare;
		smallSquare.setSize(Vector2f(cellSize - 4, cellSize - 4));
		smallSquare.setOutlineColor(Color::Black);
		smallSquare.setFillColor(Color(205, 218, 241));
		int i = (coord.y - (300 - fsize / 2 * cellSize)) / cellSize, j = (coord.x - (300 - fsize / 2 * cellSize)) / cellSize;
		smallSquare.setPosition((300 - fsize / 2 * cellSize) + j * cellSize + 2, (300 - fsize / 2 * cellSize) + i * cellSize + 2);
		window1.draw(smallSquare);
		window1.display();
		while (isChosen && window1.isOpen()) {
			Event event;
			while (window1.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window1.close();
				}
				if (Mouse::isButtonPressed(Mouse::Left)) {
					isChosen = false;
					break;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1)) {
					if (tmp.checkRow(i, 1) || tmp.checkColumn(j, 1) || tmp.checkSquare(i, j, 1) || field.checkValue(i, j, 1)) {
						MessageBox(NULL, L"Wrong cell value", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 1);
						bl[i][j] = true;
						winMenu();
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2)) {
					if (tmp.checkRow(i, 2) || tmp.checkColumn(j, 2) || tmp.checkSquare(i, j, 2) || field.checkValue(i, j, 2)) {
						MessageBox(NULL, L"Wrong cell value", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 2);
						bl[i][j] = true;
						winMenu();
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3)) {
					if (tmp.checkRow(i, 3) || tmp.checkColumn(j, 3) || tmp.checkSquare(i, j, 3) || field.checkValue(i, j, 3)) {
						MessageBox(NULL, L"Wrong cell value", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 3);
						bl[i][j] = true;
						winMenu();
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num4) || Keyboard::isKeyPressed(Keyboard::Numpad4)) {
					if (tmp.checkRow(i, 4) || tmp.checkColumn(j, 4) || tmp.checkSquare(i, j, 4) || field.checkValue(i, j, 4)) {
						MessageBox(NULL, L"Wrong cell value", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 4);
						bl[i][j] = true;
						winMenu();
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Numpad5)) {
					if (tmp.checkRow(i, 5) || tmp.checkColumn(j, 5) || tmp.checkSquare(i, j, 5) || field.checkValue(i, j, 5)) {
						MessageBox(NULL, L"Wrong cell value", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 5);
						bl[i][j] = true;
						winMenu();
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num6) || Keyboard::isKeyPressed(Keyboard::Numpad6)) {
					if (tmp.checkRow(i, 6) || tmp.checkColumn(j, 6) || tmp.checkSquare(i, j, 6) || field.checkValue(i, j, 6)) {
						MessageBox(NULL, L"Wrong cell value", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 6);
						bl[i][j] = true;
						winMenu();
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num7) || Keyboard::isKeyPressed(Keyboard::Numpad7)) {
					if (tmp.checkRow(i, 7) || tmp.checkColumn(j, 7) || tmp.checkSquare(i, j, 7) || field.checkValue(i, j, 7)) {
						MessageBox(NULL, L"Wrong cell value", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 7);
						bl[i][j] = true;
						winMenu();
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num8) || Keyboard::isKeyPressed(Keyboard::Numpad8)) {
					if (tmp.checkRow(i, 8) || tmp.checkColumn(j, 8) || tmp.checkSquare(i, j, 8) || field.checkValue(i, j, 8)) {
						MessageBox(NULL, L"Wrong cell value", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 8);
						bl[i][j] = true;
						winMenu();
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num9) || Keyboard::isKeyPressed(Keyboard::Numpad9)) {
					if (tmp.checkRow(i, 9) || tmp.checkColumn(j, 9) || tmp.checkSquare(i, j, 9) || field.checkValue(i, j, 9)) {
						MessageBox(NULL, L"Wrong cell value", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 9);
						bl[i][j] = true;
						winMenu();
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Delete) || Keyboard::isKeyPressed(Keyboard::BackSpace)) {
					if (bl[i][j] == true) {
						tmp.setCell(i, j, 0);
						bl[i][j] = false;
						isChosen = false;
						break;
					}
					else {
						MessageBox(NULL, L"Empty cell can't be deleted", L"Error!", MB_OK);
						isChosen = false;
						break;
					}
				}
			}
		}
	}

	void chooseLevelMenu() {
		RenderWindow window1(VideoMode(500, 500), "Levels");
		Texture levelsBackground, backButton;
		levelsBackground.loadFromFile("../images/game.jpg");
		backButton.loadFromFile("../images/back.png");
		Sprite settingsBg(levelsBackground), bk(backButton);
		Vector2f targetSize(500, 500), targetSize2(40, 40);
		settingsBg.setScale(targetSize.x / settingsBg.getLocalBounds().width, targetSize.y / settingsBg.getLocalBounds().height);
		bk.setScale(targetSize2.x / bk.getLocalBounds().width, targetSize2.y / bk.getLocalBounds().height);
		settingsBg.setPosition(0, 0);
		bk.setPosition(50, 430);
		Font font;
		font.loadFromFile("../book_antiqua.ttf");
		Text t0("Choose level", font, 45), t1("Easy", font, 30), t2("Medium", font, 30), t3("Hard", font, 30);
		t0.setPosition(130, 35);
		t1.setPosition(100, 120);
		t2.setPosition(100, 190);
		t3.setPosition(100, 260);
		bool isLevel = true, back = false;
		int menuNum;
		while (isLevel && window1.isOpen()) {
			Event event;
			while (window1.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window1.close();
				}
			}
			t0.setFillColor(Color::Black);
			t1.setFillColor(Color::Black);
			t2.setFillColor(Color::Black);
			t3.setFillColor(Color::Black);
			menuNum = 0;
			if (IntRect(100, 120, 70, 40).contains(Mouse::getPosition(window1))) {
				t1.setFillColor(Color(114, 167, 240));
				menuNum = 1;
			}
			if (IntRect(100, 190, 70, 40).contains(Mouse::getPosition(window1))) {
				t2.setFillColor(Color(114, 167, 240));
				menuNum = 2;
			}
			if (IntRect(100, 260, 70, 40).contains(Mouse::getPosition(window1))) {
				t3.setFillColor(Color(114, 167, 240));
				menuNum = 3;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && menuNum == 1) {
				newGame("Easy");
				isLevel = false;
				window1.close();
				game();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && menuNum == 2) {
				newGame("Medium");
				isLevel = false;
				window1.close();
				game();
			}
			if (Mouse::isButtonPressed(Mouse::Left) && menuNum == 3) {
				newGame("Hard");
				isLevel = false;
				window1.close();
				game();
			}
			bk.setColor(Color::White);
			if (IntRect(50, 430, 45, 45).contains(Mouse::getPosition(window1))) {
				bk.setColor(Color(114, 167, 240));
				back = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && back == true) {
				isLevel = false;
				window1.close();
				menu();
			}
			window1.draw(settingsBg);
			window1.draw(t0);
			window1.draw(t1);
			window1.draw(t2);
			window1.draw(t3);
			window1.draw(bk);
			window1.display();
		}
	}

	void rules() {
		RenderWindow window1(VideoMode(800, 700), "Rules");
		Texture rulesBackground, backButton;
		rulesBackground.loadFromFile("../images/rules.png");
		backButton.loadFromFile("../images/back.png");
		Sprite rulesBg(rulesBackground), bk(backButton);
		Vector2f targetSize(800, 700), targetSize2(40, 40);
		rulesBg.setScale(targetSize.x / rulesBg.getLocalBounds().width, targetSize.y / rulesBg.getLocalBounds().height);
		bk.setScale(targetSize2.x / bk.getLocalBounds().width, targetSize2.y / bk.getLocalBounds().height);
		rulesBg.setPosition(0, 0);
		bk.setPosition(50, 630);
		Font font;
		font.loadFromFile("../IgraSans.otf");
		int fontSize = 30;
		bool isRules = true, back = false;
		while (isRules && window1.isOpen()) {
			Event event;
			while (window1.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					isRules = false;
					window1.close();
				}
				bk.setColor(Color::White);
				if (IntRect(50, 610, 45, 45).contains(Mouse::getPosition(window1))) {
					bk.setColor(Color(114, 167, 240));
					back = true;
				}
				if (Mouse::isButtonPressed(Mouse::Left) && back == true) {
					isRules = false;
					window1.close();
				}
			}
			window1.draw(rulesBg);
			window1.draw(bk);
			window1.display();
		}
	}

	bool loadGame() {
		ifstream fIn("savedGame.txt");
		int k = 0;
		if (fIn.is_open()) {
			for (int i = 0; i < fsize; i++)
				for (int j = 0; j < fsize; j++) {
					//int k;
					fIn >> k;
					field.setCell(i, j, k);
				}
			for (int i = 0; i < fsize; i++)
				for (int j = 0; j < fsize; j++) {
					//int k;
					fIn >> k;
					tmp.setCell(i, j, k);
				}
			for (int i = 0; i < fsize; i++)
				for (int j = 0; j < fsize; j++) {
					//int k;
					fIn >> k;
					if (k == 1)
						bl[i][j] = true;
					else
						bl[i][j] = false;
				}
			fIn.close();
		}
		else {
			MessageBox(NULL, L"No saved game", L"Error!", MB_OK);
			return false;
		}
		return true;
	}
public:
	Game() {
		field = createFull();
		tmp = field;
	}
	void menu() {
		RenderWindow window1(VideoMode(951, 714), "Sudoku");
		Font font;
		font.loadFromFile("../book_antiqua.ttf");
		Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
		menuBackground.loadFromFile("../images/menu.jpg");
		Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
		Vector2f targetSize(951, 714);
		menuBg.setScale(targetSize.x / menuBg.getLocalBounds().width, targetSize.y / menuBg.getLocalBounds().height);
		bool isMenu = true;
		int menuNum = 0;
		Text t1("New game", font, 30), t2("Load", font, 30), t3("Rules", font, 30), t4("Quit", font, 30), t5("Sudoku game", font, 60);
		menuBg.setPosition(0, 0);
		t1.setPosition(640, 420);
		t2.setPosition(640, 470);
		t3.setPosition(640, 520);
		t4.setPosition(640, 570);
		t5.setPosition(500, 50);


		while (isMenu && window1.isOpen())
		{
			Event event;
			while (window1.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window1.close();
				}
			}

			t1.setFillColor(Color::Black);
			t2.setFillColor(Color::Black);
			t3.setFillColor(Color::Black);
			t4.setFillColor(Color::Black);
			t5.setFillColor(Color::Black);
			menuNum = 0;

			if (IntRect(640, 420, 150, 35).contains(Mouse::getPosition(window1))) {
				t1.setFillColor(Color(114, 167, 240));
				menuNum = 1;
			}
			if (IntRect(640, 470, 70, 35).contains(Mouse::getPosition(window1))) {
				t2.setFillColor(Color(114, 167, 240));
				menuNum = 2;
			}
			if (IntRect(640, 520, 70, 35).contains(Mouse::getPosition(window1))) {
				t3.setFillColor(Color(114, 167, 240));
				menuNum = 3;
			}
			if (IntRect(640, 570, 70, 35).contains(Mouse::getPosition(window1))) {
				t4.setFillColor(Color(114, 167, 240));
				menuNum = 4;
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1) {
					window1.close();
					isMenu = false;
					chooseLevelMenu();
				}
				if (menuNum == 2) {
					if (loadGame()) {
						window1.close();
						isMenu = false;
						game();
					}
				}
				if (menuNum == 3) {
					rules();
				}
				if (menuNum == 4) {
					window1.close();
					isMenu = false;
				}

			}

			window1.draw(menuBg);
			window1.draw(t1);
			window1.draw(t2);
			window1.draw(t3);
			window1.draw(t4);
			window1.draw(t5);

			window1.display();
		}
	}
};
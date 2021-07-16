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

	void drawSquare(RenderWindow& window) //int** matrix, bool** bloc, int size, int index)
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
		bigSquare.setOutlineColor(sf::Color::Black);
		bigSquare.setFillColor(sf::Color::Transparent);
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
				window.draw(smallSquare);
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
					cell.setFillColor(Color(159, 188, 229));
				}
				window.draw(cell);
			}
		}

		for (int i = 0; i < fsize; i++)
		{
			for (int j = 0; j < fsize; j++)
			{
				if (i % quad == 0 && j % quad == 0)
				{
					mediumSquare.setPosition((300 - fsize / 2 * cellSize) + j * cellSize, (300 - fsize / 2 * cellSize) + i * cellSize);
					window.draw(mediumSquare);
				}
			}
		}
		window.draw(bigSquare);
	}

	void game() {
		RenderWindow window(sf::VideoMode(750, 700), "Sudoku");
		Texture gameBackground, settingButton, helpButton;
		gameBackground.loadFromFile("../images/game.jpg");
		settingButton.loadFromFile("../images/settingsmod.png");
		helpButton.loadFromFile("../images/helpmod.png");
		Sprite gameBg(gameBackground), settings(settingButton), help(helpButton);
		Vector2f targetSize(800, 700), sizeS(40, 40), sizeH(50, 50);
		gameBg.setScale(targetSize.x / gameBg.getLocalBounds().width, targetSize.y / gameBg.getLocalBounds().height);
		settings.setScale(sizeS.x / settings.getLocalBounds().width, sizeS.y / settings.getLocalBounds().height);
		help.setScale(sizeH.x / help.getLocalBounds().width, sizeH.y / help.getLocalBounds().height);
		gameBg.setPosition(0, 0);
		settings.setPosition(690, 35);
		bool isGame = true;
		tmp.createSudoku();
		while (isGame && window.isOpen()) {
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window.close();
				}
			}
			window.draw(gameBg);
			window.draw(settings);
			drawSquare(window);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i coord = Mouse::getPosition(window);
				int i0 = 300 - fsize / 2 * cellSize, i1 = (300 - fsize / 2 * cellSize) + 9 * cellSize;
				int i = (coord.y - (300 - fsize / 2 * cellSize)) / cellSize, j = (coord.x - (300 - fsize / 2 * cellSize)) / cellSize;
				if (coord.x >= i0 && coord.x <= i1 && coord.y >= i0 && coord.y && tmp.getCell(i, j) == 0)
					chosenCell(window);
			}
			window.display();
		}
	}

	void chosenCell(RenderWindow& window) {
		bool isChosen = true;
		Vector2i coord = Mouse::getPosition(window);
		RectangleShape smallSquare;
		smallSquare.setSize(Vector2f(cellSize - 4, cellSize - 4));
		smallSquare.setOutlineColor(Color::Black);
		smallSquare.setFillColor(Color(205, 218, 241));
		int i = (coord.y - (300 - fsize / 2 * cellSize)) / cellSize, j = (coord.x - (300 - fsize / 2 * cellSize)) / cellSize;
		smallSquare.setPosition((300 - fsize / 2 * cellSize) + j * cellSize + 2, (300 - fsize / 2 * cellSize) + i * cellSize + 2);
		window.draw(smallSquare);
		window.display();
		while (isChosen && window.isOpen()) {
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}
				if (Mouse::isButtonPressed(Mouse::Left)) {
					isChosen = false;
					break;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1)) {
					if (tmp.checkRow(i, 1) || tmp.checkColumn(j, 1) || tmp.checkSquare(i, j, 1) || field.checkValue(i, j, 1)) {
						MessageBox(NULL, L"Неправильное значение ячейки", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 1);
						bl[i][j] = true;
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2)) {
					if (tmp.checkRow(i, 2) || tmp.checkColumn(j, 2) || tmp.checkSquare(i, j, 2) || field.checkValue(i, j, 2)) {
						MessageBox(NULL, L"Неправильное значение ячейки", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 2);
						bl[i][j] = true;
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3)) {
					if (tmp.checkRow(i, 3) || tmp.checkColumn(j, 3) || tmp.checkSquare(i, j, 3) || field.checkValue(i, j, 3)) {
						MessageBox(NULL, L"Неправильное значение ячейки", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 3);
						bl[i][j] = true;
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num4) || Keyboard::isKeyPressed(Keyboard::Numpad4)) {
					if (tmp.checkRow(i, 4) || tmp.checkColumn(j, 4) || tmp.checkSquare(i, j, 4) || field.checkValue(i, j, 4)) {
						MessageBox(NULL, L"Неправильное значение ячейки", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 4);
						bl[i][j] = true;
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Numpad5)) {
					if (tmp.checkRow(i, 5) || tmp.checkColumn(j, 5) || tmp.checkSquare(i, j, 5) || field.checkValue(i, j, 5)) {
						MessageBox(NULL, L"Неправильное значение ячейки", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 5);
						bl[i][j] = true;
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num6) || Keyboard::isKeyPressed(Keyboard::Numpad6)) {
					if (tmp.checkRow(i, 6) || tmp.checkColumn(j, 6) || tmp.checkSquare(i, j, 6) || field.checkValue(i, j, 6)) {
						MessageBox(NULL, L"Неправильное значение ячейки", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 6);
						bl[i][j] = true;
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num7) || Keyboard::isKeyPressed(Keyboard::Numpad7)) {
					if (tmp.checkRow(i, 7) || tmp.checkColumn(j, 7) || tmp.checkSquare(i, j, 7) || field.checkValue(i, j, 7)) {
						MessageBox(NULL, L"Неправильное значение ячейки", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 7);
						bl[i][j] = true;
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num8) || Keyboard::isKeyPressed(Keyboard::Numpad8)) {
					if (tmp.checkRow(i, 8) || tmp.checkColumn(j, 8) || tmp.checkSquare(i, j, 8) || field.checkValue(i, j, 8)) {
						MessageBox(NULL, L"Неправильное значение ячейки", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 8);
						bl[i][j] = true;
						isChosen = false;
						break;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Num9) || Keyboard::isKeyPressed(Keyboard::Numpad9)) {
					if (tmp.checkRow(i, 9) || tmp.checkColumn(j, 9) || tmp.checkSquare(i, j, 9) || field.checkValue(i, j, 9)) {
						MessageBox(NULL, L"Неправильное значение ячейки", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
					else {
						tmp.setCell(i, j, 9);
						bl[i][j] = true;
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
						MessageBox(NULL, L"Нельзя очистить изначально заполненную или пустую ячейку", L"Ошибка!", MB_OK);
						isChosen = false;
						break;
					}
				}
			}
		}
	}

	void rules() {
		RenderWindow window(sf::VideoMode(800, 700), "Sudoku");
		Texture rulesBackground, backButton;
		rulesBackground.loadFromFile("../images/rules.jpg");
		backButton.loadFromFile("../images/back.png");
		Sprite rulesBg(rulesBackground), bk(backButton);
		Vector2f targetSize(800, 700), targetSize2(45, 45);
		rulesBg.setScale(targetSize.x / rulesBg.getLocalBounds().width, targetSize.y / rulesBg.getLocalBounds().height);
		bk.setScale(targetSize2.x / bk.getLocalBounds().width, targetSize2.y / bk.getLocalBounds().height);
		rulesBg.setPosition(0, 0);
		bk.setPosition(50, 610);
		Font font;
		font.loadFromFile("../IgraSans.otf");
		int fontSize = 30;
		bool isRules = true, back = false;
		while (isRules && window.isOpen()) {
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					isRules = false;
					window.close();
					menu();
				}
				bk.setColor(Color::White);
				if (IntRect(50, 610, 45, 45).contains(Mouse::getPosition(window))) {
					bk.setColor(Color::Blue);
					back = true;
				}
				if (Mouse::isButtonPressed(Mouse::Left) && back == true) {
					isRules = false;
					window.close();
					menu();
				}
			}
			window.draw(rulesBg);
			window.draw(bk);
			window.display();
		}
	}
public:
	Game() {
		field = createFull();
		tmp = field;
		//tmp.createSudoku();
		/*for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				bl[i][j] = false;*/

	}
	void menu() {
		RenderWindow window(sf::VideoMode(951, 714), "Sudoku");
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


		while (isMenu && window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window.close();
				}
			}

			t1.setFillColor(Color::Black);
			t2.setFillColor(Color::Black);
			t3.setFillColor(Color::Black);
			t4.setFillColor(Color::Black);
			t5.setFillColor(Color::Black);
			menuNum = 0;

			if (IntRect(640, 420, 200, 40).contains(Mouse::getPosition(window))) {
				t1.setFillColor(Color::Blue);
				menuNum = 1;
			}
			if (IntRect(640, 470, 100, 40).contains(Mouse::getPosition(window))) {
				t2.setFillColor(Color::Blue);
				menuNum = 2;
			}
			if (IntRect(640, 520, 100, 40).contains(Mouse::getPosition(window))) {
				t3.setFillColor(Color::Blue);
				menuNum = 3;
			}
			if (IntRect(640, 570, 100, 40).contains(Mouse::getPosition(window))) {
				t4.setFillColor(Color::Blue);
				menuNum = 4;
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1) {
					window.close();
					game();
					isMenu = false;
				}
				if (menuNum == 2) {
					window.close();
					game();
					isMenu = false;
				}
				if (menuNum == 3) {
					window.close();
					rules();
					isMenu = false;
				}
				if (menuNum == 4) {
					window.close();
					isMenu = false;
				}

			}

			window.draw(menuBg);
			window.draw(t1);
			window.draw(t2);
			window.draw(t3);
			window.draw(t4);
			window.draw(t5);

			window.display();
		}
	}
};

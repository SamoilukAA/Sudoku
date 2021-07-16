#include "Game.h"

//void menu();

//const int fsize = 9, cellSize = 60;

//!Keyboard::isKeyPressed(Keyboard::Escape)

//void rules() {
//	RenderWindow window(sf::VideoMode(800, 700), "Sudoku");
//	Texture rulesBackground, backButton;
//	rulesBackground.loadFromFile("../images/rules.jpg");
//	backButton.loadFromFile("../images/back.png");
//	Sprite rulesBg(rulesBackground), bk(backButton);
//	Vector2f targetSize(800, 700), targetSize2(45, 45);
//	rulesBg.setScale(targetSize.x / rulesBg.getLocalBounds().width, targetSize.y / rulesBg.getLocalBounds().height);
//	bk.setScale(targetSize2.x / bk.getLocalBounds().width, targetSize2.y / bk.getLocalBounds().height);
//	rulesBg.setPosition(0, 0);
//	bk.setPosition(50, 610);
//	Font font;
//	font.loadFromFile("../IgraSans.otf");
//	int fontSize = 30;
//	bool isRules = true, back = false;
//	while (isRules && window.isOpen()) {
//		Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed) {
//				isRules = false;
//				window.close();
//				menu();
//			}
//			bk.setColor(Color::White);
//			if (IntRect(50, 610, 45, 45).contains(Mouse::getPosition(window))) {
//				bk.setColor(Color::Blue);
//				back = true;
//			}
//			if (Mouse::isButtonPressed(Mouse::Left) && back == true) {
//				isRules = false;
//				window.close();
//				menu();
//			}
//		}
//		window.draw(rulesBg);
//		window.draw(bk);
//		window.display();
//	}
//}

//void drawSquare(RenderWindow& window, sudokuF& field) //int** matrix, bool** bloc, int size, int index)
//{
//	int quadx = 3, quady = 3;
//	//int size = 9;
//
//	//int cellSize = 60, 
//	int fontSize = 30;
//
//	Font font;
//	font.loadFromFile("../book_antiqua.ttf");
//
//	RectangleShape mediumSquare;
//	mediumSquare.setSize(Vector2f(cellSize * quadx, cellSize * quady));
//	mediumSquare.setOutlineThickness(2);
//	mediumSquare.setOutlineColor(Color::Black);
//	mediumSquare.setFillColor(Color::Transparent);
//
//	RectangleShape bigSquare;
//	bigSquare.setSize(Vector2f(cellSize * fsize, cellSize * fsize));
//	bigSquare.setOutlineThickness(4);
//	bigSquare.setOutlineColor(sf::Color::Black);
//	bigSquare.setFillColor(sf::Color::Transparent);
//	bigSquare.setPosition((300 - fsize / 2 * cellSize), (300 - fsize / 2 * cellSize));
//
//	RectangleShape smallSquare;
//	smallSquare.setSize(Vector2f(cellSize, cellSize));
//	smallSquare.setOutlineThickness(1);
//	smallSquare.setOutlineColor(Color(200, 200, 200));
//	smallSquare.setFillColor(Color::White);
//
//	for (int i = 0; i < fsize; i++)
//	{
//		for (int j = 0; j < fsize; j++)
//		{
//			smallSquare.setPosition((300 - fsize / 2 * cellSize) + j * cellSize, (300 - fsize / 2 * cellSize) + i * cellSize);
//			window.draw(smallSquare);
//			string text;
//			if (field.getCell(i,j) > 0)
//			{
//				text = to_string(field.getCell(i, j));
//			}
//			else
//			{
//				text = "";
//			}
//			/*if (index % size == j && index / size == i)
//			{
//				smallSquare.setFillColor(Color(0, 255, 0, 210));
//				smallSquare.setPosition((400 - size / 2 * cellSize) + j * cellSize, (300 - size / 2 * cellSize) + i * cellSize);
//				window.draw(smallSquare);
//				smallSquare.setFillColor(sf::Color::Transparent);
//			}*/
//			
//			Text cell(text, font, fontSize);
//			cell.setPosition((300 - fsize / 2 * cellSize) + j * cellSize + fontSize / 1.3, (300 - fsize / 2 * cellSize) + i * cellSize + fontSize / 2.3);
//			cell.setFillColor(Color::Black);
//			/*if (bloc[i][j])
//			{
//				cell.setColor(Color(80, 80, 80));
//			}
//			else
//			{
//				cell.setColor(Color::Blue);
//			}*/
//
//
//			window.draw(cell);
//		}
//	}
//
//	for (int i = 0; i < fsize; i++)
//	{
//		for (int j = 0; j < fsize; j++)
//		{
//			if (i % quady == 0 && j % quadx == 0)
//			{
//				mediumSquare.setPosition((300 - fsize / 2 * cellSize) + j * cellSize, (300 - fsize / 2 * cellSize) + i * cellSize);
//				window.draw(mediumSquare);
//			}
//		}
//	}
//	window.draw(bigSquare);
//	//window.display();
//}

//void chosenCell(RenderWindow& window, sudokuF& field) {
//	bool isChosen = true;
//	Vector2i coord = Mouse::getPosition(window);
//	RectangleShape smallSquare;
//	smallSquare.setSize(Vector2f(cellSize - 4, cellSize - 4));
//	smallSquare.setOutlineColor(Color::Black);
//	smallSquare.setFillColor(Color(205, 218, 241));
//	int i = (coord.y - (300 - fsize / 2 * cellSize)) / cellSize, j = (coord.x - (300 - fsize / 2 * cellSize)) / cellSize;
//	smallSquare.setPosition((300 - fsize / 2 * cellSize) + j * cellSize + 2, (300 - fsize / 2 * cellSize) + i * cellSize + 2);
//	window.draw(smallSquare);
//	window.display();
//	while (isChosen && window.isOpen()) {
//		Event event;
//		while (window.pollEvent(event)) {
//			if (event.type == Event::Closed) {
//				window.close();
//			}
//			if (Mouse::isButtonPressed(Mouse::Left)) {
//				isChosen = false;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1)) {
//				field.setCell(i, j, 1);
//				isChosen = false;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2)) {
//				field.setCell(i, j, 2);
//				isChosen = false;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Num3) || Keyboard::isKeyPressed(Keyboard::Numpad3)) {
//				field.setCell(i, j, 3);
//				isChosen = false;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Num4) || Keyboard::isKeyPressed(Keyboard::Numpad4)) {
//				field.setCell(i, j, 4);
//				isChosen = false;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Num5) || Keyboard::isKeyPressed(Keyboard::Numpad5)) {
//				field.setCell(i, j, 5);
//				isChosen = false;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Num6) || Keyboard::isKeyPressed(Keyboard::Numpad6)) {
//				field.setCell(i, j, 6);
//				isChosen = false;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Num7) || Keyboard::isKeyPressed(Keyboard::Numpad7)) {
//				field.setCell(i, j, 7);
//				isChosen = false;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Num8) || Keyboard::isKeyPressed(Keyboard::Numpad8)) {
//				field.setCell(i, j, 8);
//				isChosen = false;
//			}
//			if (Keyboard::isKeyPressed(Keyboard::Num9) || Keyboard::isKeyPressed(Keyboard::Numpad9)) {
//				field.setCell(i, j, 9);
//				isChosen = false;
//			}
//		}		
//		/*window.draw(smallSquare);
//		window.display();*/
//	}
//}

//void game() {
//	RenderWindow window(sf::VideoMode(800, 700), "Sudoku");
//	Texture gameBackground;
//	gameBackground.loadFromFile("../images/game.jpg");
//	Sprite gameBg(gameBackground);
//	Vector2f targetSize(800, 700);
//	gameBg.setScale(targetSize.x / gameBg.getLocalBounds().width, targetSize.y / gameBg.getLocalBounds().height);
//	gameBg.setPosition(0, 0);
//	bool isGame = true;
//	sudokuF field, tmp;
//	field = createFull();
//	tmp = field;
//	tmp.createSudoku();
//	int size = 9, cellSize = 60;
//	while (isGame && window.isOpen()) {
//		Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed) {
//				window.close();
//			}
//		}
//		window.draw(gameBg);
//		drawSquare(window, tmp);
//		if (Mouse::isButtonPressed(Mouse::Left)) {
//			chosenCell(window, tmp);
//		}
//		window.display();
//	}
//}

//void menu() {
//	RenderWindow window(sf::VideoMode(951, 714), "Sudoku");
//	Font font;
//	font.loadFromFile("../book_antiqua.ttf");
//	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
//	menuBackground.loadFromFile("../images/menu.jpg");
//	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
//	Vector2f targetSize(951, 714);
//	menuBg.setScale(targetSize.x / menuBg.getLocalBounds().width, targetSize.y / menuBg.getLocalBounds().height);
//	bool isMenu = true;
//	int menuNum = 0;
//	Text t1("New game", font, 30), t2("Load", font, 30), t3("Rules", font, 30), t4("Quit", font, 30), t5("Sudoku game", font, 60);
//	menuBg.setPosition(0, 0);
//	t1.setPosition(640, 420);
//	t2.setPosition(640, 470);
//	t3.setPosition(640, 520);
//	t4.setPosition(640, 570);
//	t5.setPosition(500, 50);
//
//
//	while (isMenu && window.isOpen())
//	{
//		Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed) {
//				window.close();
//			}
//		}
//
//		t1.setFillColor(Color::Black);
//		t2.setFillColor(Color::Black);
//		t3.setFillColor(Color::Black);
//		t4.setFillColor(Color::Black);
//		t5.setFillColor(Color::Black);
//		menuNum = 0;
//
//		if (IntRect(640, 420, 200, 40).contains(Mouse::getPosition(window))) {
//			t1.setFillColor(Color::Blue);
//			menuNum = 1;
//		}
//		if (IntRect(640, 470, 100, 40).contains(Mouse::getPosition(window))) {
//			t2.setFillColor(Color::Blue);
//			menuNum = 2;
//		}
//		if (IntRect(640, 520, 100, 40).contains(Mouse::getPosition(window))) {
//			t3.setFillColor(Color::Blue);
//			menuNum = 3;
//		}
//		if (IntRect(640, 570, 100, 40).contains(Mouse::getPosition(window))) {
//			t4.setFillColor(Color::Blue);
//			menuNum = 4;
//		}
//
//		if (Mouse::isButtonPressed(Mouse::Left))
//		{
//			if (menuNum == 1) {
//				window.close();
//				game();
//				isMenu = false;
//			}
//			if (menuNum == 2) {
//				window.close();
//				game();
//				isMenu = false;
//			}
//			if (menuNum == 3) {
//				window.close();
//				rules();
//				isMenu = false;
//			}
//			if (menuNum == 4) {
//				window.close();
//				isMenu = false;
//			}
//
//		}
//
//		window.draw(menuBg);
//		window.draw(t1);
//		window.draw(t2);
//		window.draw(t3);
//		window.draw(t4);
//		window.draw(t5);
//
//		window.display();
//	}
//}

int main()
{
	setlocale(LC_ALL, "Russian");
	Game game;
	game.menu();
	//menu();
	return 0;
}
#include "Game.h"

Game::Game()
{
	this->board = GameBoard(3);
	this->board.LoadGameBoard();
}

Game::Game(int difficulty, SudokuSolver& solver) 
{
	this->board = GameBoard(3);
	board.CreateTask(difficulty, solver);
}

void Game::InitElem()
{
	backTexture.loadFromFile("Resources/Phon.png");
	backSprite.setTexture(backTexture);
	backSprite.setPosition(0, 0);
	gridTexture.loadFromFile("Resources/Grid.png");
	gridSprite.setTexture(gridTexture);
	gridSprite.setPosition(101, 50);
	cellTextures.loadFromFile("Resources/Cells.png");
	digitsSprite.setTexture(cellTextures);
	digitsSprite.setTextureRect(IntRect(66, 0, 660, 66));
	digitsSprite.setPosition(70, 700);
	chosenTexture.loadFromFile("Resources/Chosen.png");
	chosenSprite.setTexture(chosenTexture);
	chosenSprite.setPosition(70, 700);
	returnTextures.loadFromFile("Resources/Return.png");
	toMenuSprite.setTexture(returnTextures);
	toMenuSprite.setTextureRect(IntRect(0, 0, 53, 53));
	toMenuSprite.setPosition(25, 20);
	saveSprite.setTexture(returnTextures);
	saveSprite.setTextureRect(IntRect(53, 0, 53, 53));
	saveSprite.setPosition(722, 20);
	reloadSprite.setTexture(returnTextures);
	reloadSprite.setTextureRect(IntRect(106, 0, 53, 53));
	reloadSprite.setPosition(25, 103);
	winTexture.loadFromFile("Resources/Win.png");
	winSprite.setTexture(winTexture);
	winReturnTextures.loadFromFile("Resources/WinReturn.png");
    autoSprite.setTexture(returnTextures);
	autoSprite.setTextureRect(IntRect(159, 0, 53, 53));
	autoSprite.setPosition(25, 186);
	Sprite cellSprite;
	int gapX = 0;
	int gapY = 0;
	int gridSize = this->board.GetGridSize();
	int amountCells = pow(gridSize, 2);
	for (int i = 0; i < amountCells; i++)
	{
		if (i % 9 >= 3 && i % 9 <= 5)
			gapX = (i % 9) * 66 + 2;
		else if (i % 9 >= 6 && i % 9 <= 8)
			gapX = (i % 9) * 66 + 3;
		else
			gapX = (i % 9) * 66 + 1;
		gapY = (i / 9) * 66 + i / 27;
		cellsSprite.push_back(cellSprite);
		cellsSprite[i].setPosition(101 + gapX, 51 + gapY);
		cellsSprite[i].setTexture(cellTextures);
	}
}

void Game::SetTexturesCells()
{
	int gridSize = this->board.GetGridSize();
	int amountCells = pow(gridSize, 2);
	int digit;
	for (int i = 0; i < amountCells; i++)
	{
		digit = board.GetUserCells()[i / gridSize][i % gridSize];
		cellsSprite[i].setTextureRect(IntRect(66 * digit, 0, 66, 66));
		GameWindow.draw(cellsSprite[i]);
	}
}

void Game::DrawElem(bool autoSolve)
{
	GameWindow.draw(backSprite);
	GameWindow.draw(gridSprite);
	GameWindow.draw(toMenuSprite);
	GameWindow.draw(reloadSprite);
	if (!autoSolve)
	{
		GameWindow.draw(autoSprite);
		GameWindow.draw(digitsSprite);
		GameWindow.draw(chosenSprite);
		GameWindow.draw(saveSprite);
	}
}

void Game::DrawWin()
{
	GameWindow.draw(backSprite);
	GameWindow.draw(winSprite);
	toMenuSprite.setTexture(winReturnTextures);
	reloadSprite.setTexture(winReturnTextures);
	toMenuSprite.setTextureRect(IntRect(200, 0, 200, 200));
	reloadSprite.setTextureRect(IntRect(0, 0, 200, 200));
	toMenuSprite.setTextureRect(IntRect(200, 0, 200, 200));
	toMenuSprite.setPosition(100, 500);
	reloadSprite.setPosition(500, 500);
	saveSprite.~Sprite();
	GameWindow.draw(toMenuSprite);
	GameWindow.draw(reloadSprite);
}

void Game::CreateGameWindow()
{
	GameWindow.create(VideoMode(800, 800), "Sudoku", sf::Style::Close | sf::Style::Titlebar);
	this->InitElem();
	int number = 1;
	bool win = false;
	bool autoSolve = false;
	while (GameWindow.isOpen())
	{
		Vector2i click = Mouse::getPosition(GameWindow);
		int i = (click.y - 54) / 66;
		int j = (click.x - 105) / 66;
		if (GameWindow.waitEvent(GameEvent))
		{
			if (GameEvent.type == Event::Closed)
				GameWindow.close();
			if (GameEvent.type == sf::Event::MouseButtonPressed && GameEvent.mouseButton.button == sf::Mouse::Left && !win && !autoSolve &&
				digitsSprite.getGlobalBounds().contains(GameWindow.mapPixelToCoords(click)))
			{
				number = (click.x - 70) / 66;
				chosenSprite.setPosition(70 + 66 * number, 700);
				number++;
			}
			if (GameEvent.type == sf::Event::MouseButtonPressed && !win && !autoSolve &&
				gridSprite.getGlobalBounds().contains(GameWindow.mapPixelToCoords(click)))
			{
				if (GameEvent.mouseButton.button == sf::Mouse::Left)
				{
					if (!board.checkBlocked(i * board.GetGridSize() + j) && number != 10)
						board.GetUserCells()[i][j] = number;
					else if (number == 10)
						board.GetUserCells()[i][j] = board.GetReadyCells()[i][j];
				}
				else if (GameEvent.mouseButton.button == sf::Mouse::Right)
				{
					if (!board.checkBlocked(i * board.GetGridSize() + j))
						board.GetUserCells()[i][j] = 0;
				}
				if (board.GetUserCells() == board.GetReadyCells())
				{
					win = true;
				}
			}
			if (GameEvent.type == sf::Event::MouseButtonPressed && GameEvent.mouseButton.button == sf::Mouse::Left &&
				toMenuSprite.getGlobalBounds().contains(GameWindow.mapPixelToCoords(click)))
			{
				GameWindow.close();
				Menu menu;
				menu.CreateMenu();
			}
			if (GameEvent.type == sf::Event::MouseButtonPressed && GameEvent.mouseButton.button == sf::Mouse::Left && !win && !autoSolve &&
				saveSprite.getGlobalBounds().contains(GameWindow.mapPixelToCoords(click)))
			{
				board.SaveGameBoard();
			}
			if (GameEvent.type == sf::Event::MouseButtonPressed && GameEvent.mouseButton.button == sf::Mouse::Left &&
				reloadSprite.getGlobalBounds().contains(GameWindow.mapPixelToCoords(click)))
			{
				GameWindow.close();
				Menu reloadMenu;
				reloadMenu.MenuForReload();
			}
			if (GameEvent.type == sf::Event::MouseButtonPressed && GameEvent.mouseButton.button == sf::Mouse::Left && !win && !autoSolve &&
				autoSprite.getGlobalBounds().contains(GameWindow.mapPixelToCoords(click)))
			{
				autoSolve = true;
				board.GetUserCells() = board.GetReadyCells();
			}
		}
		if (!win)
		{
			DrawElem(autoSolve);
			SetTexturesCells();
		}
		else
			DrawWin();
		GameWindow.display();
	}
}

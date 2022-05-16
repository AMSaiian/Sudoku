#include "Menu.h"


Menu::Menu() 
{
}

void Menu::InitElem(bool reload)
{
	choiceBackTexture.loadFromFile("Resources/backChoice.png");
	menuTexture.loadFromFile("Resources/Phon.png");
	menuSprite.setTexture(menuTexture);
	menuSprite.setPosition(0, 0);
	if (!reload)
	{
		buttonNewTexture.loadFromFile("Resources/NewGame.png");
		buttonLoadTexture.loadFromFile("Resources/LoadGame.png");
		buttonNewSprite.setTexture(buttonNewTexture);
		buttonNewSprite.setPosition(10, 250);
	}
	difficultyTexture.loadFromFile("Resources/Difficulties.png");;
}

bool Menu::CheckSave()
{
	std::ifstream check("Save.dat");
	bool exist = check.is_open();
	check.close();
	return exist;
}

void Menu::DrawElem(bool load, bool choice)
{
	MenuWindow.draw(menuSprite);
	if (!choice)
		MenuWindow.draw(buttonNewSprite);
	if (load && !choice)
	{
		buttonLoadSprite.setTexture(buttonLoadTexture);
		buttonLoadSprite.setPosition(20, 350);
		MenuWindow.draw(buttonLoadSprite);
	}

	if (choice)
	{
		choiceBackSprite.setTexture(choiceBackTexture);
		choiceBackSprite.setPosition(0, 0);
		easySprite.setTexture(difficultyTexture);
		easySprite.setTextureRect(IntRect(0, 0, 192, 214));
		easySprite.setPosition(100, 250);
		mediumSprite.setTexture(difficultyTexture);
		mediumSprite.setTextureRect(IntRect(192, 0, 192, 214));
		mediumSprite.setPosition(300, 250);
		hardSprite.setTexture(difficultyTexture);
		hardSprite.setTextureRect(IntRect(384, 0, 192, 214));
		hardSprite.setPosition(500, 250);
		MenuWindow.draw(choiceBackSprite);
		MenuWindow.draw(easySprite);
		MenuWindow.draw(mediumSprite);
		MenuWindow.draw(hardSprite);
	}
}

void Menu::PrepareGameWithLoad()
{
	Game game;
	MenuWindow.close();
	game.CreateGameWindow();
}

void Menu::PrepareGame(int difficulty)
{
	SudokuSolver solver(3);
	Game game(difficulty, solver);
	MenuWindow.close();
	game.CreateGameWindow();
}

void Menu::CreateMenu()
{
	MenuWindow.create(VideoMode(800, 800), "Sudoku", sf::Style::Close | sf::Style::Titlebar);
	bool load = this->CheckSave();
	bool choice = 0;
	InitElem(false);
	DrawElem(load, choice);
	MenuWindow.display();
	while (MenuWindow.isOpen())
	{
		if (MenuWindow.waitEvent(MenuEvent))
		{
			if (MenuEvent.type == Event::Closed)
			{
				MenuWindow.close();
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed && MenuEvent.mouseButton.button == sf::Mouse::Left &&
				buttonNewSprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))) && !choice)
			{
				choice = 1;
				buttonNewSprite.~Sprite();
				buttonLoadSprite.~Sprite();
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed && MenuEvent.mouseButton.button == sf::Mouse::Left &&
				buttonLoadSprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))) && !choice)
			{
				PrepareGameWithLoad();
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed && MenuEvent.mouseButton.button == sf::Mouse::Left &&
				easySprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))))
			{
				PrepareGame(1);
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed && MenuEvent.mouseButton.button == sf::Mouse::Left &&
				mediumSprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))))
			{
				PrepareGame(2);
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed && MenuEvent.mouseButton.button == sf::Mouse::Left &&
				hardSprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))))
			{
				PrepareGame(3);
			}
		}
		InitElem(false);
		DrawElem(load, choice);
		MenuWindow.display();
	}
}

void Menu::MenuForReload()
{
	MenuWindow.create(VideoMode(800, 800), "Sudoku", sf::Style::Close | sf::Style::Titlebar);
	InitElem(true);
	DrawElem(false, true);
	MenuWindow.display();
	while (MenuWindow.isOpen())
	{
		if (MenuWindow.waitEvent(MenuEvent))
		{
			if (MenuEvent.type == Event::Closed)
			{
				MenuWindow.close();
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed && MenuEvent.mouseButton.button == sf::Mouse::Left &&
				easySprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))))
			{
				PrepareGame(1);
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed && MenuEvent.mouseButton.button == sf::Mouse::Left &&
				mediumSprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))))
			{
				PrepareGame(2);
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed && MenuEvent.mouseButton.button == sf::Mouse::Left &&
				hardSprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))))
			{
				PrepareGame(3);
			}
		}
		InitElem(false);
		DrawElem(false, true);
		MenuWindow.display();
	}
}

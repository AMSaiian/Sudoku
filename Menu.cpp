#include "Menu.h"


Menu::Menu() 
{
}

void Menu::InitElem()
{
	choiceBackTexture.loadFromFile("Resources/backChoice.png");
	menuTexture.loadFromFile("Resources/Phon.png");
	buttonNewTexture.loadFromFile("Resources/NewGame.png");
	buttonLoadTexture.loadFromFile("Resources/LoadGame.png");
	difficultyTexture.loadFromFile("Resources/Difficulties.png");

	menuSprite.setTexture(menuTexture);
	buttonNewSprite.setTexture(buttonNewTexture);

	menuSprite.setPosition(0, 0);
	buttonNewSprite.setPosition(10, 250);

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
	if (choice != 1)
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

void Menu::CreateMenu()
{
	MenuWindow.create(VideoMode(800, 800), "Sudoku", sf::Style::Close | sf::Style::Titlebar);
	bool load = this->CheckSave();
	bool choice = 0;		
	while (MenuWindow.isOpen())
	{
		while (MenuWindow.pollEvent(MenuEvent))
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
				std::cout << "clicked load game" << "\n";
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed && MenuEvent.mouseButton.button == sf::Mouse::Left &&
				choiceBackSprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))))
			{
				Game game(3);
				MenuWindow.close();
				game.CreateGameWindow();
			}
		}
		InitElem();
		DrawElem(load, choice);
		MenuWindow.display();
	}
}

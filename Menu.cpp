#include "Menu.h"


Menu::Menu() {

    RenderWindow MenuWindow(VideoMode(800, 800), "Menu");

    menuTexture.loadFromFile("Menu.png");
	buttonNewTexture.loadFromFile("NewGame.png");
    menuSprite.setTexture(menuTexture);
	buttonNewSprite.setTexture(buttonNewTexture);
    menuSprite.setPosition(0, 0);
	buttonNewSprite.setPosition(10, 250);
    MenuWindow.clear();
    MenuWindow.draw(menuSprite);
	MenuWindow.draw(buttonNewSprite);
	std::ifstream check("Save.dat");
	if (!check.is_open())
	{
		buttonLoadTexture.loadFromFile("LoadGame.png");
		buttonLoadSprite.setTexture(buttonLoadTexture);
		buttonLoadSprite.setPosition(20, 350);
		MenuWindow.draw(buttonLoadSprite);
	}
	check.close();
    MenuWindow.display();

	while (MenuWindow.isOpen())
	{
		while (MenuWindow.pollEvent(MenuEvent))
		{
			if (MenuEvent.type == Event::Closed)
				MenuWindow.close();
			if (MenuEvent.type == sf::Event::MouseButtonPressed && 
				buttonNewSprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))))
			{
					std::cout << "clicked new game" << "\n";
			}
			if (MenuEvent.type == sf::Event::MouseButtonPressed &&
				buttonLoadSprite.getGlobalBounds().contains(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow))))
			{
					std::cout << "clicked load game" << "\n";
			}
		}
	}
}
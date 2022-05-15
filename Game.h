#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "GameBoard.h"


using namespace sf;

class Game
{
private:
	RenderWindow GameWindow;
	Texture backTexture, buttonPauseTexture, gridTexture, cellTextures, chosenTexture;
	Sprite backSprite, buttonPauseSprite, gridSprite, digitsSprite, chosenSprite;
	std::vector<Sprite> cellsSprite;
	GameBoard board;
	Event GameEvent{};
	void InitElem();
	void SetTexturesCells();
public:
	Game();
	Game(int difficulty);
	void CreateGameWindow();
};
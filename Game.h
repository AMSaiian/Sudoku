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
	Texture backTexture, buttonPauseTexture, gridTexture, cellTextures, chosenTexture, returnTextures;
	Sprite backSprite, buttonPauseSprite, gridSprite, digitsSprite, chosenSprite, toMenuSprite, saveSprite;
	std::vector<Sprite> cellsSprite;
	GameBoard board;
	Event GameEvent{};
	void InitElem();
	void SetTexturesCells();
	void DrawElem();
public:
	Game();
	Game(int difficulty, SudokuSolver& solver);
	void CreateGameWindow();
};
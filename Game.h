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
	Texture backTexture, winTexture, buttonPauseTexture, gridTexture, cellTextures, chosenTexture, returnTextures, winReturnTextures;
	Sprite backSprite, winSprite, buttonPauseSprite, gridSprite, digitsSprite, chosenSprite, toMenuSprite, saveSprite, reloadSprite;
	std::vector<Sprite> cellsSprite;
	GameBoard board;
	Event GameEvent{};
	void InitElem();
	void SetTexturesCells();
	void DrawElem();
	void DrawWin();
public:
	Game();
	Game(int difficulty, SudokuSolver& solver);
	void CreateGameWindow();
};
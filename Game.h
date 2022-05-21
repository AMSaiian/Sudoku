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
	Sprite backSprite, winSprite, buttonPauseSprite, gridSprite, digitsSprite, chosenSprite, toMenuSprite, saveSprite, reloadSprite, autoSprite;
	std::vector<Sprite> cellsSprite;
	std::vector<Sprite> chosenCells;
	Event GameEvent{};
	GameBoard board;
	SudokuSolver solver;
	void InitElem();
	void SetTexturesCells();
	void DrawElem(bool autoSolve);
	void DrawWin();
	void PointUncorrect();
	void UnpointUncorrect(Vector2f cell);
public:
	Game();
	Game(int difficulty);
	void CreateGameWindow();
};
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Game.h"

using namespace sf;

class Menu
{
private:
	RenderWindow MenuWindow;
	Texture menuTexture, buttonNewTexture, buttonLoadTexture, choiceBackTexture, difficultyTexture;
	Sprite menuSprite, buttonNewSprite, buttonLoadSprite, choiceBackSprite, easySprite, mediumSprite, hardSprite;
	Event MenuEvent{};
	void InitElem();
	bool CheckSave();
	void DrawElem(bool load, bool choice);
	void PrepareGameWithLoad();
	void PrepareGame(int difficulty);
public:
	Menu();
	void CreateMenu();
};
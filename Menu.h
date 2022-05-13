#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;

class Menu
{
	RenderWindow MenuWindow;
	Texture menuTexture, buttonNewTexture, buttonLoadTexture, choiceBackTexture, difficultyTexture;
	Sprite menuSprite, buttonNewSprite, buttonLoadSprite, choiceBackSprite, easySprite, mediumSprite, hardSprite;
	Event MenuEvent{};
	void InitElem();
	bool CheckSave();
	void DrawElem(bool load, bool choice);
public:
	Menu();
	void CreateMenu();
};
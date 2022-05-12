#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;

class Menu
{
	RenderWindow MenuWindow;
	Texture menuTexture, buttonNewTexture, buttonLoadTexture;
	Sprite menuSprite, buttonNewSprite, buttonLoadSprite;
	Event MenuEvent{};
public:
	Menu();
};
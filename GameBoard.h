#pragma once
#include <vector>

class GameBoard
{
public:
	std::vector<std::vector<int>> readyCells;
	std::vector<std::vector<int>> userCells;
public:
	GameBoard();
	void CreateBasicBoard();
	void MixRows();
	void MixColumns();
	void MixDistrictsVertically();
	void MixDistrictsHorizontally();
	void TransposingBoard();
	void CreateDecision();
};


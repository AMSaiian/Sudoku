#pragma once
#include <vector>

class GameBoard
{
private:
	int boxSize;
	int gridSize;
	std::vector<std::vector<int>> readyCells;
	std::vector<std::vector<int>> userCells;
public:
	GameBoard(int boxSize);
	void CreateBasicBoard();
	void MixRows();
	void MixColumns();
	void MixDistrictsVertically();
	void MixDistrictsHorizontally();
	void TransposingBoard();
	void CreateDecision();
	int GetBoxSize();
};


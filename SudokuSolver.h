#pragma once
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <string>

class SudokuSolver
{
private:
	std::map<std::tuple<int, int, int>, std::set<std::tuple<int, int, int>>> tableColumns;
	std::map<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>> tableRows;
	int boxSize;
	int gridSize;
	void fillRows();
	void fillColumns();
	std::vector<std::set<std::tuple<int, int, int>>> select(std::tuple<int, int, int> row);
	void deselect(std::tuple<int, int, int> row, std::vector<std::set<std::tuple<int, int, int>>> columns);
	std::vector<std::tuple<int, int, int>>
		alghorithmX(std::vector<std::tuple<int, int, int>> cover = std::vector<std::tuple<int, int, int>>());
public:
	SudokuSolver(int boxSize = 3);
	std::vector<std::vector<int>> solveSudoku(std::vector<std::vector<int>> grid, std::tuple<int, int, int> limitation = std::tuple<int, int, int>());
	std::tuple<int, int> findCellForHint(std::vector<std::vector<int>> grid);
};
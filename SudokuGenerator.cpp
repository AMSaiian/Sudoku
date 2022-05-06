#include "SudokuGenerator.h"

std::vector<std::vector<int>> solveSudoku(std::vector<std::vector<int>> grid, int columnSize, int rowSize)
{
	int gridSize = rowSize * columnSize;
	std::vector<std::tuple<std::string, std::tuple<int, int>>> X_set;
	std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple <int, int>>>> Y_set;
	fillXset(X_set, gridSize);
	fillYset(Y_set, rowSize, columnSize, gridSize);
	std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>> X_mod = findExactCover(X_set, Y_set);
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (grid[i][j])
			{
				select(X_mod, Y_set, std::tuple<int, int, int>(i, j, grid[i][j]));
			}
		}
	}
	std::vector<std::vector<int>> grid2;
	return grid2;
}

void fillXset(std::vector<std::tuple<std::string, std::tuple<int, int>>>& X_set, int gridSize)
{
	std::tuple<std::string, std::tuple<int, int>> tempTuple;
	std::string limitation = "rc";
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			std::get<0>(tempTuple) = limitation;
			std::get<0>(std::get<1>(tempTuple)) = i;
			std::get<1>(std::get<1>(tempTuple)) = j;
			X_set.push_back(tempTuple);
		}
	}
	limitation = "rn";
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 1; j < gridSize + 1; j++)
		{
			std::get<0>(tempTuple) = limitation;
			std::get<0>(std::get<1>(tempTuple)) = i;
			std::get<1>(std::get<1>(tempTuple)) = j;
			X_set.push_back(tempTuple);
		}
	}
	limitation = "cn";
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 1; j < gridSize + 1; j++)
		{
			std::get<0>(tempTuple) = limitation;
			std::get<0>(std::get<1>(tempTuple)) = i;
			std::get<1>(std::get<1>(tempTuple)) = j;
			X_set.push_back(tempTuple);
		}
	}
	limitation = "bn";
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 1; j < gridSize + 1; j++)
		{
			std::get<0>(tempTuple) = limitation;
			std::get<0>(std::get<1>(tempTuple)) = i;
			std::get<1>(std::get<1>(tempTuple)) = j;
			X_set.push_back(tempTuple);
		}
	}
}

void fillYset(std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple <int, int>>>>& Y_set,
	          int rows, int columns, int gridSize)
{
	for (int number = 1; number < gridSize + 1; number++)
	{
		for (int column = 0; column < gridSize; column++)
		{
			for (int row = 0; row < gridSize; row++)
			{
				int box = (row / rows) * rows + (column / columns);
				std::vector<std::tuple<std::string, std::tuple <int, int>>> 
					limitations{std::tuple<std::string, std::tuple <int, int>>(std::string("rc"), std::tuple<int, int>(row, column)),
								std::tuple<std::string, std::tuple <int, int>>(std::string("rn"), std::tuple<int, int>(row, number)),
								std::tuple<std::string, std::tuple <int, int>>(std::string("cn"), std::tuple<int, int>(column, number)),
								std::tuple<std::string, std::tuple <int, int>>(std::string("bn"), std::tuple<int, int>(box, number))};
				Y_set[std::tuple<int, int, int>(row, column, number)] = limitations;
			}
		}
	}
}

std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>> 
findExactCover(std::vector<std::tuple<std::string, std::tuple<int, int>>> X_set, 
	           std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple<int, int>>>>& Y_set)
{
	std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>> X_mod;
	std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple<int, int>>>> :: iterator itY = Y_set.begin();
	for (int i = 0; i < std::size(Y_set); i++)
	{
		std::tuple<int, int, int> key = itY->first;
		std::vector<std::tuple<std::string, std::tuple<int, int>>> value = itY->second;
		for (int j = 0; j < std::size(value); j++)
		{
			X_mod[value[j]].insert(key);
		}
		itY++;
	}
	return X_mod;
}

std::vector<std::set<std::tuple<int, int, int>>>
select(std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>>& X_mod, 
	   std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple<int, int>>>>& Y_set,
	   std::tuple<int, int, int> row)
{
	std::vector<std::set<std::tuple<int, int, int>>> columns;
	for (int i = 0; i < std::size(Y_set[row]); i++)
	{
		std::tuple<std::string, std::tuple<int, int>> xlimitation = Y_set[row][i];
		for (std::set<std::tuple<int, int, int>>::iterator number = X_mod[xlimitation].begin(); number != X_mod[xlimitation].end(); number++)
		{
			std::tuple<int, int, int> cell = *number;
			for (int j = 0; j < std::size(Y_set[cell]); j++)
			{
				std::tuple<std::string, std::tuple<int, int>> ylimitation = Y_set[cell][j];
				if (xlimitation != ylimitation)
				{
					X_mod[ylimitation].erase(cell);
				}
			}
		}
		columns.push_back(X_mod[xlimitation]);
		X_mod.erase(xlimitation);
	}
	return columns;
}

void deselect(std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>>& X_mod,
	          std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple<int, int>>>>& Y_set,
	          std::tuple<int, int, int> row, std::vector<std::set<std::tuple<int, int, int>>> columns)
{
	for (int i = std::size(Y_set[row]) - 1; i > -1; i--)
	{
		std::tuple<std::string, std::tuple<int, int>> xlimitation = Y_set[row][i];
		X_mod[xlimitation] = columns.back();
		columns.pop_back();
		for (std::set<std::tuple<int, int, int>>::iterator number = X_mod[xlimitation].begin(); number != X_mod[xlimitation].end(); number++)
		{
			std::tuple<int, int, int> cell = *number;
			for (int j = 0; j < std::size(Y_set[cell]); j++)
			{
				std::tuple<std::string, std::tuple<int, int>> ylimitation = Y_set[cell][j];
				if (xlimitation != ylimitation)
				{
					X_mod[ylimitation].insert(cell);
				}
			}
		}
	}
}
#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(int boxSize)
{
	this->boxSize = boxSize;
	this->gridSize = boxSize * boxSize;
}

std::vector<std::vector<int>> SudokuSolver::solveSudoku(std::vector<std::vector<int>> grid, std::tuple<int,int,int> limitation)
{
	if (tableRows.empty())
		fillRows();
	std::vector<std::tuple<std::string, std::tuple <int, int>>> tempRow;
	if (limitation != std::tuple<int, int, int>())
	{
		tempRow = tableRows[limitation];
		tableRows.erase(limitation);
	}
	fillColumns();
	std::vector<std::tuple<int, int, int>> solution;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (grid[i][j])
			{
				solution.push_back(std::tuple<int, int, int>(i, j, grid[i][j]));
				select(std::tuple<int, int, int>(i, j, grid[i][j]));
			}
		}
	}
	solution = alghorithmX(solution);
	if (!tempRow.empty())
		tableRows[limitation] = tempRow;
	if (solution.empty())
	{
		return std::vector<std::vector<int>>(gridSize, std::vector<int>(gridSize, 0));
	}
	else
	{
		for (int i = 0; i < size(solution); i++)
		{
			int row = std::get<0>(solution[i]);
			int column = std::get<1>(solution[i]);
			int number = std::get<2>(solution[i]);
			grid[row][column] = number;
		}
	}
	return grid;
}

void SudokuSolver::fillRows()
{
	for (int number = 1; number < gridSize + 1; number++)
	{
		for (int column = 0; column < gridSize; column++)
		{
			for (int row = 0; row < gridSize; row++)
			{
				int box = (row / boxSize) * boxSize + (column / boxSize);
				std::vector<std::tuple<std::string, std::tuple <int, int>>>
					limitations{ std::tuple<std::string, std::tuple <int, int>>(std::string("rc"), std::tuple<int, int>(row, column)),
								std::tuple<std::string, std::tuple <int, int>>(std::string("rn"), std::tuple<int, int>(row, number)),
								std::tuple<std::string, std::tuple <int, int>>(std::string("cn"), std::tuple<int, int>(column, number)),
								std::tuple<std::string, std::tuple <int, int>>(std::string("bn"), std::tuple<int, int>(box, number)) };
				tableRows[std::tuple<int, int, int>(row, column, number)] = limitations;
			}
		}
	}
}

void SudokuSolver::fillColumns()
{
	std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple<int, int>>>> ::iterator itR = tableRows.begin();
	for (int i = 0; i < std::size(tableRows); i++)
	{
		std::tuple<int, int, int> value = itR->first;
		std::vector<std::tuple<std::string, std::tuple<int, int>>> key = itR->second;
		for (int j = 0; j < std::size(key); j++)
		{
			tableColumns[key[j]].insert(value);
		}
		itR++;
	}
}

std::vector<std::set<std::tuple<int, int, int>>> SudokuSolver::select(std::tuple<int, int, int> row)
{
	std::vector<std::set<std::tuple<int, int, int>>> columns;
	for (int i = 0; i < std::size(tableRows[row]); i++)
	{
		std::tuple<std::string, std::tuple<int, int>> xlimitation = tableRows[row][i];
		for (std::set<std::tuple<int, int, int>>::iterator number = tableColumns[xlimitation].begin(); 
			 number != tableColumns[xlimitation].end(); number++)
		{
			std::tuple<int, int, int> cell = *number;
			for (int j = 0; j < std::size(tableRows[cell]); j++)
			{
				std::tuple<std::string, std::tuple<int, int>> ylimitation = tableRows[cell][j];
				if (xlimitation != ylimitation)
				{
					tableColumns[ylimitation].erase(cell);
				}
			}
		}
		columns.push_back(tableColumns[xlimitation]);
		tableColumns.erase(xlimitation);
	}
	return columns;
}

void SudokuSolver::deselect(std::tuple<int, int, int> row, std::vector<std::set<std::tuple<int, int, int>>> columns)
{
	for (int i = std::size(tableRows[row]) - 1; i > -1; i--)
	{
		std::tuple<std::string, std::tuple<int, int>> xlimitation = tableRows[row][i];
		tableColumns[xlimitation] = columns.back();
		columns.pop_back();
		for (std::set<std::tuple<int, int, int>>::iterator number = tableColumns[xlimitation].begin();
			 number != tableColumns[xlimitation].end(); number++)
		{
			std::tuple<int, int, int> cell = *number;
			for (int j = 0; j < std::size(tableRows[cell]); j++)
			{
				std::tuple<std::string, std::tuple<int, int>> ylimitation = tableRows[cell][j];
				if (xlimitation != ylimitation)
				{
					tableColumns[ylimitation].insert(cell);
				}
			}
		}
	}
}

std::vector<std::tuple<int, int, int>>
SudokuSolver::alghorithmX(std::vector<std::tuple<int, int, int>> cover)
{
	if (tableColumns.empty())
		return cover;
	else
	{
		int min = 10;
		std::tuple<std::string, std::tuple<int, int>> minKey;
		for (std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>>::iterator itX = tableColumns.begin();
			itX != tableColumns.end(); itX++)
		{
			if (std::size(itX->second) < min)
			{
				min = std::size(itX->second);
				minKey = itX->first;
			}
		}
		for (int i = 0; i < min; i++)
		{
			std::set<std::tuple<int, int, int>>::iterator subset = tableColumns[minKey].begin();
			std::advance(subset, i);
			cover.push_back(*subset);
			std::vector<std::set<std::tuple<int, int, int>>> temp = select(cover.back());
			std::vector<std::tuple<int, int, int>> solution = alghorithmX(cover);
			if (!solution.empty())
				return solution;
			deselect(cover.back(), temp);
			cover.pop_back();
		}
		return std::vector<std::tuple<int, int, int>>();
	}
}
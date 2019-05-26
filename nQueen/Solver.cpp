#include "Solver.h"
#include <sstream>
#include <vector>
Solver::Solver(int problemsize)
{
	this->size = problemsize;
	this->board = new int[problemsize];
	this->conflicts = new int[problemsize];
}

Solver::~Solver()
{
	if (board != nullptr)
		delete[] board;
	if (conflicts != nullptr)
		delete[] conflicts;
}

void Solver::Solve()
{
	int numberOfTries = 0;
	bool isFound = false;
	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		board[i] = rand() % size;
	}

	while (!(isFound = isGoal(this->board, this->conflicts, this->size))
		and
		numberOfTries < 200
		)
	{
		vector<int> temp;
		for (int i = 0; i < size; i++)
		{
			if (conflicts[i])
			{
				temp.push_back(i);
			}
		}
		auto randomColumn = temp.at(rand() %temp.size());
		//for (randomColumn = 0; randomColumn < size && !conflicts[randomColumn]; randomColumn++);

		if (
			/*hasConflict(this->board, board[randomColumn], randomColumn, size)*/
			conflicts[randomColumn]
			)
		{
			conflictsInColumn(this->board, randomColumn, this->conflicts, this->size);

			auto minConflictsIndex = minValue(this->conflicts, size, randomColumn);

			this->board[randomColumn] = minConflictsIndex;
		}
		numberOfTries++;
	}
	if (!isFound)
	{
		Solve();
	}
}

string Solver::toString() const
{
	stringstream ss;

	for (int i = 0; i < this->size; i++)
	{
		ss << board[i] << " ";
	}
	return ss.str();
}

void Solver::updateConflicts(const int* board, int* conflicts, const int size)
{
	resetArray(conflicts, size);
	int queenRow = -1;
	for (int queenColumn = 0; queenRow < size; queenColumn++)
	{
		queenRow = board[queenColumn];

		//west
		for (int i = 1; i < size && queenColumn - i >= 0; i++)
		{
			if (board[queenColumn - i] == queenRow)
			{
				conflicts[queenColumn]++;
			}
		}

		//eset
		for (int i = 1; i < size && queenColumn + i < size; i++)
		{
			if (board[queenColumn + i] == queenRow)
			{
				conflicts[queenColumn]++;
			}
		}

		//north-west
		for (int i = 1; i < size && queenColumn - i >= 0 && queenRow - i >= 0; i++)
		{
			if (board[queenColumn - i] == queenRow - i)
			{
				conflicts[queenColumn]++;
			}
		}

		//north-eset
		for (int i = 1; i < size && queenColumn + i < size && queenRow - i >= 0; i++)
		{
			if (board[queenColumn + i] == queenRow - i)
			{
				conflicts[queenColumn]++;
			}
		}

		//south-west
		for (int i = 1; i < size && queenColumn - i >= 0 && queenRow + i < size; i++)
		{
			if (board[queenColumn - i] == queenRow + i)
			{
				conflicts[queenColumn]++;
			}
		}

		//south-eset
		for (int i = 1; i < size && queenColumn + i < size && queenRow + i < size; i++)
		{
			if (board[queenColumn + i] == queenRow + i)
			{
				conflicts[queenColumn]++;
			}
		}
	}
}

void Solver::resetArray(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		array[i] = 0;
	}
}

void Solver::conflictsInColumn(const int* board, int queenColumn, int* conflicts, int size)
{
	resetArray(conflicts, size);

	for (int queenRow = 0; queenRow < size; queenRow++)
	{
		//west
		for (int i = 1; i < size && queenColumn - i >= 0; i++)
		{
			if (board[queenColumn - i] == queenRow)
			{
				conflicts[queenRow]++;
			}
		}

		//eset
		for (int i = 1; i < size && queenColumn + i < size; i++)
		{
			if (board[queenColumn + i] == queenRow)
			{
				conflicts[queenRow]++;
			}
		}

		//north-west
		for (int i = 1; i < size && queenColumn - i >= 0 && queenRow - i >= 0; i++)
		{
			if (board[queenColumn - i] == queenRow - i)
			{
				conflicts[queenRow]++;
			}
		}

		//north-eset
		for (int i = 1; i < size && queenColumn + i < size && queenRow - i >= 0; i++)
		{
			if (board[queenColumn + i] == queenRow - i)
			{
				conflicts[queenRow]++;
			}
		}

		//south-west
		for (int i = 1; i < size && queenColumn - i >= 0 && queenRow + i < size; i++)
		{
			if (board[queenColumn - i] == queenRow + i)
			{
				conflicts[queenRow]++;
			}
		}

		//south-eset
		for (int i = 1; i < size && queenColumn + i < size && queenRow + i < size; i++)
		{
			if (board[queenColumn + i] == queenRow + i)
			{
				conflicts[queenRow]++;
			}
		}
	}
}

bool Solver::isGoal(const int* board, int *conflictsBuffer, int size)
{
	updateConflicts(board, conflicts, size);

	for (int i = 0; i < size; i++)
	{
		if (conflicts[i] != 0)
		{
			return false;
		}
	}
	return true;
}

int Solver::minValue(const int* array, int size, int column)
{
	auto minIndex = board[column] == 0 ? 1 : 0;
	auto min = array[minIndex];
	for (int i = 0; i < size; i++)
	{
		if (i == board[column] && array[i] != min)
			continue;
		if (array[i] < min)
		{
			min = array[i];
			minIndex = i;
		}
	}
	return minIndex;
}

bool Solver::hasConflict(const int* board, int queenRow, int queenColumn, int size) const
{
	//west
	for (int i = 1; i < size && queenColumn - i >= 0; i++)
	{
		if (board[queenColumn - i] == queenRow)
		{
			return true;
		}
	}

	//eset
	for (int i = 1; i < size && queenColumn + i < size; i++)
	{
		if (board[queenColumn + i] == queenRow)
		{
			return true;
		}
	}

	//north-west
	for (int i = 1; i < size && queenColumn - i >= 0 && queenRow - i >= 0; i++)
	{
		if (board[queenColumn - i] == queenRow - i)
		{
			return true;
		}
	}

	//north-eset
	for (int i = 1; i < size && queenColumn + i < size && queenRow - i >= 0; i++)
	{
		if (board[queenColumn + i] == queenRow - i)
		{
			return true;
		}
	}

	//south-west
	for (int i = 1; i < size && queenColumn - i >= 0 && queenRow + i < size; i++)
	{
		if (board[queenColumn - i] == queenRow + i)
		{
			return true;
		}
	}

	//south-eset
	for (int i = 1; i < size && queenColumn + i < size && queenRow + i < size; i++)
	{
		if (board[queenColumn + i] == queenRow + i)
		{
			return true;
		}
	}
	return false;
}


#pragma once
#include <string>
#include <ctime>
using namespace std;

class Solver
{
private:
	int* board;
	int* conflicts;
	int size;

public:
	Solver(int problemsize);
	~Solver();
	void Solve();
	string toString() const;

private:
	void updateConflicts(const int* board, int* conflicts, const int size);
	void resetArray(int* array, int size);
	void conflictsInColumn(const int* board, int column, int* conflicts, int size);
	bool isGoal(const int* board, int *conflictsBuffer, int size);
	int minValue(const int* array, int size, int column);
	bool hasConflict(const int* board, int row, int column, int size) const;
};
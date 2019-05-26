#include <iostream>
#include "Solver.h"

using namespace std;

int main()
{
	int n = 200;

	Solver solver(n);

	solver.Solve();

	cout << solver.toString();

}

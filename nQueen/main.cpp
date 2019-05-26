

#include <iostream>
#include <ctime>


int main()
{
	
	int n = 8;

	int* board = new int[n];

	srand(time(0));

	for (int i = 0; i < n; i++)
	{
		board[i] = rand() % n;
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << board[i] << " ";
	}
}

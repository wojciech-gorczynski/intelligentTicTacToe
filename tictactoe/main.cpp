#include "tictactoe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace tictactoe;

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	TicTacToe obj;
	obj.gamePlay();

	return 0;
}
#include "tictactoe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


namespace tictactoe
{

	TicTacToe::TicTacToe() {
		m_currentPlayer = HUMAN;
		m_isFinished = NO;
		for (int currentGrid = FIRST_GRID; currentGrid < END_OF_ARRAY; ++currentGrid)
			m_gameBoard[currentGrid] = EMPTY;
	}


	/*
	This method draws player who will start the game
	The human player takes symbol of a circle and a boolean value of 0
	The CPU player takes symbol of a cross and a boolean value of 1
	*/

	void TicTacToe::drawPlayer()
	{
		m_currentPlayer = (std::rand() % PLAYERDRAW);
		std::cout << "Your symbol is circle" << '\n';
		std::cout << ((m_currentPlayer == HUMAN) ? "You will start the game" : "Computer will start the game") << '\n';
		std::cout << '\n';
	}

	/*
	This method shows current state of the grids on a game board.
	*/

	void TicTacToe::showGameBoard() const
	{
		std::cout << '\n';
		std::cout << '0' << " " << '1' << " " << '2' << '\n';
		for (int currentGrid = FIRST_GRID; currentGrid < END_OF_ARRAY; ++currentGrid) {
			if (!(currentGrid % 3))
				std::cout << '\n';
			if (m_gameBoard[currentGrid] == EMPTY)
				std::cout << '_' << " ";
			else if (m_gameBoard[currentGrid] == CIRCLE)
				std::cout << 'O' << " ";
			else if (m_gameBoard[currentGrid] == CROSS)
				std::cout << 'X' << " ";
		}
		std::cout << '\n';
		std::cout << '\n';
		std::cout << '6' << " " << '7' << " " << '8' << '\n';
		std::cout << '\n';
	}

	/*
	This method is used to place a symbol of the current player on a game board.
	*/
	void TicTacToe::makeMove()
	{
		short chosenGrid;//This variable is used to provide which grid the current player wants to change into his symbol
		bool isFirstCpuMove = YES;//This variable will remain true until CPU player will take its first move
		short numberOfMoves = 0;//This is the counter of every move,it will help to calculate the result
		while (!m_isFinished)//This loop will be repeated until the game is over
		{
			showGameBoard();
			if (m_currentPlayer == HUMAN) {//If the current player is 0-human
				std::cout << "Choose field from 0 to 8" << '\n';
				std::cin >> chosenGrid;
				if (m_gameBoard[chosenGrid] == EMPTY) {//Checks if chosen grid is still empty
					m_gameBoard[chosenGrid] = CIRCLE;//If it is still empty,now it turns into the circle grid
					++numberOfMoves;//Counter of all moves is incremented
					checkIfWon(numberOfMoves);//Checks if the game is still not over
					m_currentPlayer = CPU;//Flips the current player into CPU
				}
				else if ((chosenGrid > LAST_GRID || chosenGrid < FIRST_GRID)) {//Checks if the provided grid value is correct
					std::cout << "You are out of board." << '\n';
				}
				else {//Checks if chosen grid is available
					std::cout << "This field is already taken.Pick another one." << '\n';
				}
			}
			else if (m_currentPlayer == CPU) {//If current player is 1-CPU,this condition takes place
				if (isFirstCpuMove) {//If this is the first CPU move,this condition will be done
					while (true) {//As long as there is no correct value given,this loop will be used
						chosenGrid = (std::rand() % END_OF_ARRAY);//Draws the grid value between 0-8
						if (m_gameBoard[chosenGrid] == EMPTY) {//If the drawn grid value is available
							m_gameBoard[chosenGrid] = CROSS;
							isFirstCpuMove = NO;//After first CPU move,this loop will never happen again,so this boolean is switched
							++numberOfMoves;//Number of Moves counter is incremented
							m_currentPlayer = HUMAN;//switches into the human player
							break;
						}
					}
				}
				else {//If this is not the first CPU move,the following code will run
					bool isThereNeighbour = NO;//This variable will change into true if there is a neighbour found
					for (int currentGrid = FIRST_GRID; currentGrid < END_OF_ARRAY; ++currentGrid) {//Checks all grids
						if ((m_gameBoard[currentGrid] == EMPTY)//this condition checks if there is available a neighbour on the grid
							&& ((m_gameBoard[currentGrid - 1] == CROSS) || (m_gameBoard[currentGrid + 1] == CROSS))) {//proposed by the for loop,and if the proposed field is empty
							m_gameBoard[currentGrid] = CROSS;
							isThereNeighbour = YES;
							++numberOfMoves;
							checkIfWon(numberOfMoves);
							m_currentPlayer = HUMAN;
							break;
						}
					}
					if (isThereNeighbour == NO) {
						while (true) {
							chosenGrid = (std::rand() % END_OF_ARRAY);
							if (m_gameBoard[chosenGrid] == EMPTY) {
								m_gameBoard[chosenGrid] = CROSS;
								++numberOfMoves;
								checkIfWon(numberOfMoves);
								m_currentPlayer = HUMAN;
								break;
							}
						}
					}
				}
				system("CLS");//refreshes the screen with current state of game board
			}
		}
	}

	/*
	This method holds the conditions of winning the game.If current state of the game is similar to any
	of the following conditions,it means the game is over.
	Every condition has its own rules which are:
	First condition(winCombinationRowOne)-grids [0][1][2] are all circles/crosses
	Second condition(winCombinationRowTwo)-grids [3][4][5] are all circles/crosses
	Third condition(winCombinationRowThree)-grids [6][7][8] are all circles/crosses
	Fourth condition(winCombinationColumnOne)-grids [0][3][6] are all circles/crosses
	Fifth condition(winCombinationColumnTwo)-grids [1][4][7] are all circles/crosses
	Sixth condition(winCombinationColumnThree)-grids [2][5][8] are all circles/crosses
	Seventh condition(winCombinationCrossFromRowOne)-grids [0][4][8] are all circles/crosses
	Eighth condition(winCombinationCrossFromRowThree)-grids [2][4][6] are all circles/crosses
	If all grids are taken but no combination is true,there is no winner and the game ends with a draw.
	*/
	void TicTacToe::checkIfWon(const short&numberOfMoves)
	{
		int first = m_gameBoard[0] + m_gameBoard[1] + m_gameBoard[2];
		int second = m_gameBoard[3] + m_gameBoard[4] + m_gameBoard[5];
		int third = m_gameBoard[6] + m_gameBoard[7] + m_gameBoard[8];
		int fourth = m_gameBoard[0] + m_gameBoard[3] + m_gameBoard[6];
		int fifth = m_gameBoard[1] + m_gameBoard[4] + m_gameBoard[7];
		int sixth = m_gameBoard[2] + m_gameBoard[5] + m_gameBoard[8];
		int seventh = m_gameBoard[0] + m_gameBoard[4] + m_gameBoard[8];
		int eight = m_gameBoard[2] + m_gameBoard[4] + m_gameBoard[6];

		if ((first == CROSSWON || first == CIRCLEWON) || (second == CROSSWON || second == CIRCLEWON) || (third == CROSSWON || third == CIRCLEWON)
			|| (fourth == CROSSWON || fourth == CIRCLEWON) || (fifth == CROSSWON || fifth == CIRCLEWON) || (sixth == CROSSWON || sixth == CIRCLEWON)
			|| (seventh == CROSSWON || seventh == CIRCLEWON) || (eight == CROSSWON || eight == CIRCLEWON)) {
			showGameBoard();
			std::cout << '\n';
			std::cout << ((m_currentPlayer == HUMAN) ? "You win!" : "You lose") << '\n';
			m_isFinished = YES;
			system("pause");
		}

		else if (!(m_isFinished) && (numberOfMoves == END_OF_ARRAY)) {
			showGameBoard();
			std::cout << '\n';
			std::cout << "Draw!" << '\n';
			m_isFinished = YES;
			system("pause");
		}
	}

	/*
	This method will start the game and finish the game
	*/

	void TicTacToe::gamePlay()
	{
		drawPlayer();
		while (m_isFinished == NO) {
			makeMove();
		}
	}
}
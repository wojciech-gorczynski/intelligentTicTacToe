#pragma once

/*
Tic-tac-toe the game.
Rules:
Game takes place on a board sized of one dimensional fixed array sized of 9 grids(typed of enum).
The goal of a game is to be the first player to get three of his symbols placed in a horizontal,
vertical or diagonal row.
At the beginning of the game,application draws a player who will place his symbol first.The human player
takes circle(O) as his symbol,while the CPU player plays with a crosses(X).
After placing a symbol,the round is over and the next player places his symbol on the chosen empty field.
Game ends either if one of the players gets three symbols in a horizontal,
vertical or diagonal row-which means he is the winner,or nobody is able to place three symbols in a row-
this situation means game ends with a draw.
*/

namespace tictactoe
{
	class TicTacToe
	{
	private:
		const static int m_gameBoardSize = 9;//Total size of the game board
		enum GridSize { FIRST_GRID = 0, LAST_GRID = 8, END_OF_ARRAY = 9 };//Holds sizes of the board
		enum Players { HUMAN, CPU, PLAYERDRAW };
		enum Choices { NO, YES };
		enum Sign { EMPTY = 0, CROSS = 5, CIRCLE = 50, CROSSWON = 15, CIRCLEWON = 150 };//Here the players symbols are hold.Each player has the value of his symbol,winning values will be used to calculate if someone gets three symbols in a row
		Sign m_gameBoard[m_gameBoardSize];//Board built with enum Symbol grids
		bool m_isFinished;//This boolean value will check if the game is over
		bool m_currentPlayer;//This boolean value controls which player takes move right now
	public:

		TicTacToe();
		void drawPlayer();//	This method draws player who will start the game
		void showGameBoard() const;//	This method shows current state of the grids on a game board.
		void makeMove(); //	This method is used to place a symbol of the current player on a game board.
		void checkIfWon(const short &numberOfMoves);//	This method holds the conditions of winning the game.If current state of the game is similar to any
		void gamePlay();//	This method will start the game and finish the game
	};
}
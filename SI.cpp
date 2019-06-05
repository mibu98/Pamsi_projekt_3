#include "SI.h"
#include <vector>


// Konstruktor
SI::SI()
{

}


// Destruktor
SI::~SI()
{

}


// Inicjalizacja graczy, wybor gracza SI
void SI::initPlayers()
{
	int option;

	std::cout << "Pick your player: " << std::endl
		<< "1. X " << std::endl
		<< "2. O " << std::endl;

	std::cin >> option;

	if (option == 1)
	{
		humanPlayer = 'X';
		SIPlayer = 'O';
	}
	else
	{
		humanPlayer = 'O';
		SIPlayer = 'X';
	}
}


char SI::getSIPlayer() const
{
	return SIPlayer;
}


char SI::getHumanPlayer() const
{
	return humanPlayer;
}


void SI::setDepth(int t_depth)
{
	depth = t_depth;
}


// Wybor najlepszego ruchu SI
SIMove SI::getBestMove(board& board, char player, int t_depth)
{

	// Glebokosc rekurencji

	if (t_depth == 0)
	{
		return SIMove(0);
	}

	// Przypadek podstawowy
	char rv = board.IsGameOver(); // X/Y - x/y wygrywa, D - remis (draw), N - No draw/no win

	if (rv == SIPlayer)
	{
		return SIMove(10);
	}
	else if(rv == humanPlayer)
	{
		return SIMove(-10);
	}
	else if(rv == 'D')
	{
		return SIMove(0);
	}

	// RPrzypadek rekursywny
	std::vector<SIMove> moves;

	for (int iLn = 0; iLn < board.getSize(); iLn++)
	{
		for (int jCol = 0; jCol < board.getSize(); jCol++)
		{
			if (board.getValue(iLn, jCol) == '-')
			{
				SIMove move;

				move.line = iLn;
				move.column = jCol;

				board.InsertSign(iLn, jCol, player);


				if (player == SIPlayer) // SI -> gracz
				{
					move.score = getBestMove(board, humanPlayer, t_depth - 1).score;
				}
				else // gracz -> SI
				{
					move.score = getBestMove(board, SIPlayer, t_depth - 1).score;
				}


				moves.push_back(move);
				board.InsertSign(iLn, jCol, '-');
			}
		}
	}

	int bestMove = 0;
	if (player == SIPlayer)
	{
		int bestScore = -100000000;
		for (unsigned int i = 0; i < moves.size(); i++)
		{
			if (moves[i].score > bestScore)
			{
				bestMove = i;
				bestScore = moves[i].score;

			}
		}
	}
	else
	{
		int bestScore = 100000000;
		for (unsigned int i = 0; i < moves.size(); i++)
		{
			if (moves[i].score < bestScore)
			{
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	return moves[bestMove];
}


// wykonanie ruchu SI
void SI::performMove(board& board, char player)
{

	SIMove bestMove = getBestMove(board, SIPlayer, depth);

	board.InsertSign(bestMove.line, bestMove.column, SIPlayer);
}


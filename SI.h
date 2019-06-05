#pragma once
#include "Board.h"


struct SIMove
{
	SIMove() {};
	SIMove(int t_score) : score(t_score) {};
	SIMove(int t_line, int t_column) : line(t_line), column(t_column) {};

	int line{-2};
	int column{-2};
	int score{0};
};


class SI
{
private:

	char humanPlayer;
	char SIPlayer;
	int depth{ 2 };

	SIMove getBestMove(board& board, char player, int t_depth);

public:
	SI();
	~SI();

	char getSIPlayer() const;
	char getHumanPlayer() const;

	void setDepth(int t_depth);

	void initPlayers();
	void performMove(board& board, char player);
};


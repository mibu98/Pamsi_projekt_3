#pragma once
#include <iostream>
#include <assert.h>


class board
{
private:
	int BoardSize{ 0 }; // Wielkosc planszy w formacie n x n
	int SignNumberInRow{ 0 }; // ile znakow do wygranej
	int MaxMovesNumber{ 0 }; // maksymalna liczba ruchow na danej planszy
	int CurrentMovesNumber{ 0 }; // ilosc ruchow juz wykonanych

	int LastInsertLine{ 0 };
	int LastInsertColumn{ 0 };
	char LastMovePlayer{'K'};

	char** BoardArray;

public:
	board(int boardSize, int t_signNumberInRow);
	~board();

	void ClearBoardArray();

	void InsertSign(int t_ln, int t_col, char value);

	int getSize() const;
	char getValue(int line, int column) const;

	char IsWin() const;
	char IsDraw() const;
	char IsGameOver() const;

	void ShowBoard() const;
	void ShowBoardStats() const;
};


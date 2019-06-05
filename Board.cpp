#include "Board.h"


// Konstruktor
board::board(int boardSize, int t_signNumberInRow)
{

	BoardSize = boardSize;
	SignNumberInRow = t_signNumberInRow;
	MaxMovesNumber = BoardSize * BoardSize;

	BoardArray = new char* [BoardSize];

	for (int i = 0; i < BoardSize; i++)
	{
		BoardArray[i] = new char[BoardSize];
	}
}

//---------------------------------------------------------------------------------------------------
// Destruktor
board::~board()
{

}


// Wypelnia plansze '-'
void board::ClearBoardArray()
{

	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			BoardArray[i][j] = '-';
		}
	}
}

// Pokazuje plansze
void board::ShowBoard() const
{

	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			std::cout << BoardArray[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// Pokazuje parametry planszy
void board::ShowBoardStats() const
{

	std::cout << std::endl <<  "========== BOARD STATS ==========" << std::endl
		<< "Board size: " << BoardSize << " x " << BoardSize << std::endl
		<< "Number of signs in a row to win: " << SignNumberInRow << std::endl
		<< "Max number of moves: " << MaxMovesNumber << std::endl
		<< "Current number of moves: " << CurrentMovesNumber << std::endl;
}

// Sprawdza czy po ostatnim ruchu ktos wygral, jesli nie, zwraca 'N'
char board::IsWin() const
{

	int t_lastIndexCol = LastInsertColumn;
	int t_lastIndexLn = LastInsertLine;
	char t_player = LastMovePlayer;

	// Liczniki:
	int horizontalCounter{ 1 };
	int verticalCounter{ 1 };
	int lrDiagonalCounter{ 1 };
	int rlDiagonalCounter{ 1 };

	// HORIZONTAL:
	// do prawej
	for (int i = t_lastIndexCol + 1; i < BoardSize && BoardArray[t_lastIndexLn][i] == t_player; i++)
		horizontalCounter++;

	// do lewej
	for (int i = t_lastIndexCol - 1; i >= 0 && BoardArray[t_lastIndexLn][i] == t_player; i--)
		horizontalCounter++;

	// VERTICAL:
	// do gory
	for (int i = t_lastIndexLn - 1; i >= 0 && BoardArray[i][t_lastIndexCol] == t_player; i--)
		verticalCounter++;

	// do dolu
	for (int i = t_lastIndexLn + 1; i < BoardSize && BoardArray[i][t_lastIndexCol] == t_player; i++)
		verticalCounter++;

	// LEFT TO RIGHT DIAGONAL
	// do gory
	for (int l = t_lastIndexLn - 1, c = t_lastIndexCol + 1; l >= 0 && c < BoardSize
		&& BoardArray[l][c] == t_player; l--, c++)
	{
		lrDiagonalCounter++;
	}

	// do dolu
	for (int l = t_lastIndexLn + 1, c = t_lastIndexCol - 1; l < BoardSize && c >= 0
		&& BoardArray[l][c] == t_player; l++, c--)
	{
		lrDiagonalCounter++;
	}

	// RIGHT TO LEFT DIAGONAL
	// do gory
	for (int l = t_lastIndexLn - 1, c = t_lastIndexCol - 1; l >= 0 && c >= 0
		&& BoardArray[l][c] == t_player; l--, c--)
	{
		rlDiagonalCounter++;
	}

	// do dolu
	for (int l = t_lastIndexLn + 1, c = t_lastIndexCol + 1; l < BoardSize && c < BoardSize
		&& BoardArray[l][c] == t_player; l++, c++)
	{
		rlDiagonalCounter++;
	}


	if (horizontalCounter >= SignNumberInRow || verticalCounter >= SignNumberInRow
		|| lrDiagonalCounter >= SignNumberInRow || rlDiagonalCounter >= SignNumberInRow)
	{

		return t_player; // wygrana O lub X
	}
	else
	{
		return 'N'; // Brak wygranej
	}
}

// Jesli plansza pelna i brak wygranej -> remis (draw)
char board::IsDraw() const
{
	if (CurrentMovesNumber >= MaxMovesNumber) // jesli remis
		return 'D'; // wyswietl draw
	else
		return 'N';
}

// uzycie IsWin i IsDraw
char board::IsGameOver() const
{
	// wygrana X lub O:
	char win = IsWin();
	char draw = IsDraw();

	if (win == 'X' || win == 'O') // Jeden z graczy wygrywa
	{
		return win;
	}
	else if (draw == 'D') // Remis
	{
		return draw;
	}
	else
	{
		return 'N';
	}
}

void board::InsertSign(int t_ln, int t_col, char t_player)
{

	assert(t_ln >= 0 && t_col >= 0 && t_ln < BoardSize && t_col < BoardSize);
	assert(t_player == 'X' || t_player == 'O' || t_player == '-');

	BoardArray[t_ln][t_col] = t_player;

	if (t_player == 'X' || t_player == 'O')
	{
		CurrentMovesNumber++;

		LastInsertLine = t_ln;
		LastInsertColumn = t_col;
		LastMovePlayer = t_player;
	}
	else
	{
		CurrentMovesNumber--;
	}
}


// sprawdza wielkos planszy
int board::getSize() const
{
	return BoardSize;
}

// Wartosc komorki
char board::getValue(int line, int column) const
{
	return BoardArray[line][column];
}





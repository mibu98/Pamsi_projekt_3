#include "Gra.h"

#define HOW_BIG 5 //wielkosc planszy
#define WIN_CONDITION 5 //ilosc znakow do wygranej
#define DEPTH_ 5 //glebokosc rekurencji: dla planszy 3x3 polecana 10, dla planszy 4x4 polecana 7



// Konstruktor
Gra::Gra()
{
	//std::cout << "Gra CONSTRUCTOR " << std::endl;
}


//Destruktor
Gra::~Gra()
{
	//std::cout << "Gra DESTRUCTOR " << std::endl;
}


// Game start menu: pvp, pve, exit
int Gra::GameStartMenu() const
{
	int i{};

	std::cout << "TIC TAC TOE" << std::endl
		<< "---------- GAME MENU ----------" << std::endl
		<< "1. PvP " << std::endl
		<< "2. vs SI " << std::endl
		<< "3. Exit " << std::endl;

	std::cin >> i;

	return i;
}

// Zmiana gracza (ruchu)
void Gra::SwitchPlayer()
{

	assert(CurrentPlayer == 'X' || CurrentPlayer == 'O');

	if (CurrentPlayer == 'X')
		CurrentPlayer = 'O';
	else
		CurrentPlayer = 'X';
}


// Zmiana ruchu vs SI
void Gra::SwitchPVEPlayer()
{
	assert(CurrentPVEPlayer == 'A' || CurrentPVEPlayer == 'H');

	if (CurrentPVEPlayer == 'H')
		CurrentPVEPlayer = 'A';
	else
		CurrentPVEPlayer = 'H';
}


// Jesli gracz to X - zaczyna
void Gra::SetCurrentPVEPlayer(char t_humanPlayer)
{

	if (t_humanPlayer == 'X')
		CurrentPVEPlayer = 'H';
	else
		CurrentPVEPlayer = 'A';
}

// Kto sie rusza (vs SI)
char Gra::getCurrentPVEPlayer()
{
	return CurrentPVEPlayer;
}


// Get current player
char Gra::getPlayerType() const
{
	return CurrentPlayer;
}

void Gra::showTheEndResult(char t_endResult) const
{
	assert(t_endResult == 'X' || t_endResult == 'O' || t_endResult == 'D');

	if (t_endResult == 'X' || t_endResult == 'O')
		std::cout << "********** Player " << t_endResult << " wins! ********** " << std::endl;
	else if (t_endResult == 'D')
		std::cout << " Draw! " << std::endl;
}

// Ruch SI
void Gra::SIMove(board& board, char player, SI t_SI)
{
	// std::cout << "It's SI move <------ " << std::endl;
	t_SI.performMove(board, player);
}

// Ruch gracza
void Gra::PlayerMove(board& board, char player)
{
	int line{-1};
	int column{-1};

	assert(player == 'X' || player == 'O');

	std::cout << "You're " << player << " player" << std::endl;

	bool goodField = false;
	while(goodField == false)
	{
		std::cout << "Line: ";
		std::cin >> line;
		std::cout << "Column: ";
		std::cin >> column;

		line = line -1; column = column -1;

		if (line >= 0 && line < board.getSize() && column >= 0 && column < board.getSize()
			&& board.getValue(line, column) == '-')
		{
			goodField = true;
		}
		else
		{
			std::cout << "Wrong co-ordinates, try agSIn: " << std::endl;
			goodField = false;
		}
	}

	board.InsertSign(line, column, player);
}

// Start Gry
void Gra::StartGame()
{
	board board(HOW_BIG,WIN_CONDITION); // Tworzy miejsce na plansze (wielkosc, ile w linii do wygranej)
	SI minimax;

	minimax.setDepth(DEPTH_); // Dla 4x4 7 jest ok

	board.ClearBoardArray();
	board.ShowBoardStats();

	char isEnd = 'N';

	switch (GameStartMenu())
	{
	case 1:
		std::cout << "Start PVP game " << std::endl;

		while (isEnd == 'N')
		{
			board.ShowBoard();

			PlayerMove(board, CurrentPlayer);
			board.ShowBoard();
			isEnd = board.IsGameOver();

			SwitchPlayer();

			if (isEnd == 'N')
			{
				PlayerMove(board, CurrentPlayer);
				board.ShowBoard();
				isEnd = board.IsGameOver();

				SwitchPlayer();
			}
		}

		break;
	case 2:
		std::cout << "Start PVE game " << std::endl;

		minimax.initPlayers();
		SetCurrentPVEPlayer(minimax.getHumanPlayer());

		board.ShowBoard();

		while (isEnd == 'N')
		{
			if (getCurrentPVEPlayer() == 'A')
				SIMove(board, CurrentPlayer, minimax);
			else
				PlayerMove(board, CurrentPlayer);

			board.ShowBoard();

			isEnd = board.IsGameOver();

			SwitchPVEPlayer();
			SwitchPlayer();
		}

		break;

	default:
		std::cout << "Exit game" << std::endl;

		break;
	}

	showTheEndResult(isEnd);

	system("PAUSE");
}

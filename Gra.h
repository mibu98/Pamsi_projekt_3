#pragma once
#include "SI.h"

class Gra
{
private:
	char CurrentPlayer = 'X'; // X zawsze staruje pierwszy
	char CurrentPVEPlayer = 'N'; // czlowiek czy SI

public:
	Gra();
	~Gra();

	void SIMove(board& board, char player, SI t_SI);
	void PlayerMove(board& board, char player);

	void StartGame();
	void SwitchPlayer();
	void SwitchPVEPlayer();

	int GameStartMenu() const;
	char getPlayerType() const;

	void SetCurrentPVEPlayer(char t_humanPlayer);
	char getCurrentPVEPlayer();

	void showTheEndResult(char t_endResult) const;
};


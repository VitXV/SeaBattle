#pragma once
#include "Player.h"
#include "SeaBattleField.h"
// Game Logic

class SeaBattle
{
	Field& field1;
	Field& field2;

	Player& p1;
	Player& p2;
	int turn=0;
	int changing=0;
public:
	SeaBattle(Player& PLAYER1, Player& PLAYER2);
	Player& getP1() const;
	Player& getP2() const;
	Player& getCurrP() const;
	Field& getField1() const;
	Field& getField2() const;
	Field& getCurrF() const;
	Field& getNCurrF() const;

	void start();
	bool isOver() const;
	void Move(int y, int x);
	bool NextPlayersTurn();
};

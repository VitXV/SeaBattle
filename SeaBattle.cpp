#include "SeaBattle.h"

SeaBattle::SeaBattle(Player& PLAYER1, Player& PLAYER2) : p1(PLAYER1), p2(PLAYER2), field1(PLAYER1.field), field2(PLAYER2.field) {};

bool SeaBattle::isOver() const
{
	return(field1.countAlive() == 0 || field2.countAlive() == 0);
}

Player& SeaBattle::getP1() const
{
	return p1;
}

Player& SeaBattle::getP2() const
{
	return p2;
}

Player& SeaBattle::getCurrP() const
{
	if (turn % 2 == 0)
		return p1;
	else
		return p2;
}

Field& SeaBattle::getField1() const
{
	return field1;
}

Field& SeaBattle::getField2() const
{
	return field2;
}

Field& SeaBattle::getCurrF() const
{
	if (turn % 2 == 0)
		return field1;
	else
		return field2;
}

Field& SeaBattle::getNCurrF() const
{
	if (turn % 2 == 0)
		return field2;
	else
		return field1;
}

void SeaBattle::start()
{
	turn = 0;
	changing = 0;
	getNCurrF().ChangeVisibility();
}

void SeaBattle::Move(int y, int x)
{
	changing = getNCurrF().CheckCell(y,x);
	turn += changing;
}

bool SeaBattle::NextPlayersTurn()
{
	if (changing == 1)
		return true;
	return false;
}
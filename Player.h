#pragma once
#include <string>
#include "SeaBattleField.h"

class Player
{
protected:
	std::string name;
	Field field;
public:
	virtual std::string getName() const;
	virtual bool isHuman()=0;
	friend class SeaBattle;
};

class Human : public Player
{
public:
	Human(std::string NAME);
	Human(std::string NAME, Field FIELD);
	std::string getName() const;
	bool isHuman();
};

class Computer : public Player
{
public:
	Computer(std::string NAME);
	Computer(std::string NAME, Field FIELD);
	std::string getName() const;
	bool isHuman();
};
#pragma once
#include "SeaBattle.h"

class Interface
{
protected:
	SeaBattle& game;
public:
	Interface(SeaBattle& GAME);
	virtual void ShowFields() = 0;
	virtual void play() = 0;
};

class Console : public Interface
{
public:
	Console(SeaBattle& GAME);
	void ShowFields();
	void play();
};
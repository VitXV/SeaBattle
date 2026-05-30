#include "Player.h"
#include <random>
#include <time.h>

std::string Player::getName() const
{
	return name;
}

Human::Human(std::string NAME)
{
	name = NAME;
	field.ShipPlacementGenerator();
}

Human::Human(std::string NAME, Field FIELD)
{
	name = NAME;
	field = FIELD;
}

std::string Human::getName() const
{
	return std::string(name) + " (Human)";
}

bool Human::isHuman()
{
	return true;
}

Computer::Computer(std::string NAME)
{
	name = NAME;
	field.ShipPlacementGenerator();
}

Computer::Computer(std::string NAME, Field FIELD)
{
	name = NAME;
	field = FIELD;
}

std::string Computer::getName() const
{
	return std::string(name) + " (Computer)";
}

bool Computer::isHuman()
{
	return false;
}
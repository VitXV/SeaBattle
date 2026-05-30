#pragma once
#include "SeaBattleCell.h"

const int FIELD_HEIGHT = 10;
const int FIELD_WIDTH = 10;

class Field
{
    Cell field[FIELD_HEIGHT][FIELD_WIDTH];

    bool isShipNearby(int y, int x);
    bool CheckPlacement(int y, int x, int length, int dir);
    bool ShipPlacement(int y, int x, int length, int dir);

    void Paint(int y, int x, int length, int dir);
    void ShipDestroying(int y, int x);

public:
    int countAlive();

    Cell& getCell(int y, int x);

    void ClearField();
    void ShipPlacementGenerator();

    void ChangeVisibility();

    int CheckCell(int y, int x);
};

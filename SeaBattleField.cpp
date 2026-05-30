#include <string>
#include <random>
#include <time.h>
#include "SeaBattleField.h" 

bool Field::isShipNearby(int y, int x)
{
    for (int i = y - 1; i < y + 2; i++)
    {
        for (int j = x - 1; j < x + 2; j++)
        {
            if (i < 0 || i>=FIELD_HEIGHT || j < 0 || j>=FIELD_WIDTH)
                continue;
            if (field[i][j].value == SHIP)
                return true;
        }
    }
    return false;
}

bool Field::CheckPlacement(int y, int x, int length, int dir)
{
    if (length == 0)
        return true;

    if (y<0 || y>=FIELD_HEIGHT || x<0 || x>=FIELD_WIDTH)
        return false;
    if (isShipNearby(y,x))
        return false;

    if (dir == 0)
        y -= 1;
    if (dir == 1)
        y += 1;
    if (dir == 2)
        x -= 1;
    if (dir == 3)
        x += 1;

    return CheckPlacement(y, x, length-1, dir);
}

bool Field::ShipPlacement(int y, int x, int length, int dir)
{
    if (CheckPlacement(y, x, length, dir))
    {
        for (int i = 0; i < length; i++)
        {
            if (dir == 0)
                field[y-i][x].value = SHIP;
            else if (dir == 1)
                field[y+i][x].value = SHIP;
            else if (dir == 2)
                field[y][x-i].value = SHIP;
            else if (dir == 3)
                field[y][x+i].value = SHIP;
        }
        return true;
    }
    return false;
}

void shift(int* M, int index, int n)
{
    int buffer = M[index];
    for (int i=index; i < n-1; i++)
        M[i] = M[i+1];
    M[n-1] = buffer;
}

void Field::ShipPlacementGenerator()
{
    int dirs[] = { 0, 1, 2, 3 }; // North, South, West, East

    for (int types = 1; types < 5; types++)
    {
        // gc = generator counter
        for (int gc=0; gc < types;) // until required num of ships hasnt been created yet
        {
            int y = rand() % FIELD_HEIGHT;
            int x = rand() % FIELD_WIDTH;
            for (int dcounter = 0; dcounter < 4; dcounter++) // trying all directions
            {
                int d = rand() % (4 - dcounter); // index in directions array
                if (ShipPlacement(y, x, (5-types), d))
                {
                    gc++;
                    break;
                }
                shift(dirs, d, 4);
            }
        }

        for (int i = 0; i < 4; i++)
            dirs[i] = i;
    }
}

void Field::Paint(int y, int x, int length, int dir)
{
    int i = -1;
    if (dir == 0)
    {
        for (i; i<=length; i++)
        {
            if (y+i<FIELD_HEIGHT && y+i>=0 && x-1>=0)
            {
                field[y + i][x - 1].value = MISS;
                field[y + i][x - 1].hidden = false;
            }
            if (y+i<FIELD_HEIGHT && y+i>=0 && x+1<FIELD_WIDTH)
            {
                field[y + i][x + 1].value = MISS;
                field[y + i][x + 1].hidden = false;
            }
        }
        if (y-1 >= 0)
        {
            field[y-1][x].value = MISS;
            field[y-1][x].hidden = false;
        }
        if (y + length < FIELD_HEIGHT)
        {
            field[y + length][x].value = MISS;
            field[y + length][x].hidden = false;
        }
    }
    else
    {
        for (i; i <= length; i++)
        {
            if (x+i<FIELD_WIDTH && x+i>=0 && y-1>=0)
            {
                field[y - 1][x + i].value = MISS;
                field[y - 1][x + i].hidden = false;
            }
            if (x+i<FIELD_WIDTH && x+i>=0 && y+1<FIELD_HEIGHT)
            {
                field[y + 1][x + i].value = MISS;
                field[y + 1][x + i].hidden = false;
            }
        }
        if (x-1 >= 0)
        {
            field[y][x - 1].value = MISS;
            field[y][x - 1].hidden = false;
        }
        if (x + length < FIELD_WIDTH)
        {
            field[y][x + length].value = MISS;
            field[y][x + length].hidden = false;
        }
    }
}

void Field::ShipDestroying(int y, int x)
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if ((i+j)%2 == 1)
            {
                if (y+i-1>=0 && y+i-1<FIELD_HEIGHT && x+j-1>=0 && x+j-1<FIELD_WIDTH)
                {
                    if (field[y + i - 1][x + j - 1].value == SHIP)
                        return;
                }
            }
        }
    }

    int dir=0;
    int length=1;

    int startY = y;
    int endY = y;

    int startX = x;
    int endX = x;

    bool VerticalPart1 = false;
    bool VerticalPart2 = false;

    bool HorizontalPart1 = false;
    bool HorizontalPart2 = false;

    if (y-1 >= 0)
    {
        if (field[y - 1][x].value == DESTROYED)
            VerticalPart1 = true;
    }
    if (y+1 < FIELD_HEIGHT)
    {
        if (field[y+1][x].value == DESTROYED)
            VerticalPart2 = true;
    }

    if (x-1 >= 0)
    {
        if (field[y][x-1].value == DESTROYED)
            HorizontalPart1 = true;
    }
    if (x+1 < FIELD_WIDTH)
    {
        if (field[y][x+1].value == DESTROYED)
            HorizontalPart2 = true;
    }

    if (VerticalPart1 || VerticalPart2)
    {
        dir = 0;
        for (int i = 1; ;i++)
        {
            if (y-i < 0)
                break;
            if (!(field[y-i][x].value == DESTROYED || field[y-i][x].value == SHIP))
                break;
            startY = y - i;
        }

        for (int i = 1; ;i++)
        {
            if (y+i >= FIELD_HEIGHT)
                break;
            if (!(field[y+i][x].value == DESTROYED || field[y+i][x].value == SHIP))
                break;
            endY = y + i;
        }
        length = endY - startY+1;
    }
    else if (HorizontalPart1 || HorizontalPart2)
    {
        dir = 1;
        for (int i = 1; ;i++)
        {
            if (x-i < 0)
                break;
            if (!(field[y][x-i].value == DESTROYED || field[y][x-i].value == SHIP))
                break;
            startX = x - i;
        }

        for (int i = 1; ;i++)
        {
            if (x+i >= FIELD_WIDTH)
                break;
            if (!(field[y][x+i].value == DESTROYED || field[y][x+i].value == SHIP))
                break;
            endX = x + i;
        }
        length = endX - startX+1;
    }

    bool isDestroyed = true;
    for (int i = 0; i < length; i++)
    {
        if (dir == 0)
        {
            if (field[startY + i][x].value != DESTROYED)
            {
                isDestroyed = false;
                break;
            }
        }
        else
        {
            if (field[y][startX + i].value != DESTROYED)
            {
                isDestroyed = false;
                break;
            }
        }
    }
    if (isDestroyed)
        Paint(startY, startX, length, dir);
}

int Field::CheckCell(int y, int x)
{
    if (field[y][x].value == SHIP)
    {
        field[y][x].hidden = false;
        field[y][x].value = DESTROYED;
        ShipDestroying(y, x);
        return 2;
    }
    else if (field[y][x].value == EMPTY)
    {
        field[y][x].hidden = false;
        field[y][x].value = MISS;
        return 1;
    }
    else
        return 0;
}

void Field::ChangeVisibility()
{
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
            field[y][x].visible = !field[y][x].visible;
    }
}

int Field::countAlive()
{
    int res = 0;
    for (int y = 0; y < FIELD_HEIGHT;y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            if (field[y][x].value == SHIP)
                res++;
        }
    }
    return res;
}

Cell& Field::getCell(int y, int x)
{
    return field[y][x];
}

void Field::ClearField()
{
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
            field[y][x].value = EMPTY;
    }
}
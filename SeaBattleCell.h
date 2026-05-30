#pragma once

enum Values : char
{
    EMPTY = '.',
    MISS = '*',
    SHIP = '#',
    DESTROYED = 'X'
};

class Cell
{
    Values value = EMPTY;
    bool hidden = true;
    bool visible = true;

public:
    char getValue()
    {
        return value;
    }

    bool isHidden()
    {
        return hidden;
    }

    bool isVisible()
    {
        return visible;
    }

    friend class Field;
};
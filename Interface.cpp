#include "Interface.h"
#include <iostream>
#include <iomanip>
#include <string>

Interface::Interface(SeaBattle& GAME) : game(GAME) {}
Console::Console(SeaBattle& GAME) : Interface(GAME) {}

void Console::ShowFields()
{
    int padding = (3*2 + FIELD_WIDTH*2 - game.getP1().getName().length()) / 2;
    std::cout << std::setw(padding) << ' ' << game.getP1().getName();
    std::cout << std::setw(padding) << ' ';

    padding = (3*2 + FIELD_WIDTH*2 - game.getP2().getName().length()) / 2;
    std::cout << std::setw(padding) << ' ' << game.getP2().getName();

    std::cout << '\n' << "   ";
    for (char column = 'A'; column < 'A' + FIELD_WIDTH; column++)
        std::cout << column << ' ';

    std::cout << "     ";
    for (char column = 'A'; column < 'A' + FIELD_WIDTH; column++)
        std::cout << column << ' ';

    std::cout << '\n';

    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        std::cout << std::setw(2) << y + 1;
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            Cell& cell = game.getField1().getCell(y, x);
            if (!cell.isHidden())
                std::cout << ' ' << cell.getValue();
            else if (cell.isVisible())
                std::cout << ' ' << cell.getValue();
            else
                std::cout << ' ' << EMPTY;
        }
        std::cout << "   ";

        std::cout << std::setw(2) << y + 1;
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            Cell cell = game.getField2().getCell(y, x);
            if (!cell.isHidden())
                std::cout << ' ' << cell.getValue();
            else if (cell.isVisible())
                std::cout << ' ' << cell.getValue();
            else
                std::cout << ' ' << EMPTY;
        }
        std::cout << '\n';
    }
}

void Console::play()
{
    game.start();

    char c;
    int y;
    int x;

    bool PvP=false;
    if (game.getP1().isHuman() && game.getP2().isHuman())
        PvP = true;

    while (!game.isOver())
    {
        Player& curr = game.getCurrP();
        if (PvP && game.NextPlayersTurn())
        {
            game.getField1().ChangeVisibility();
            game.getField2().ChangeVisibility();
        }

        if (curr.isHuman())
        {
            std::cout << '\n';
            ShowFields();
            do
            {
                std::cout << '\n' << "   Its " << curr.getName() << " turn: ";
                std::cin >> c >> x;

                if (!std::cin)
                {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    c = ' ';
                    x = 0;
                }
            } while (!(x > 0 && x <= FIELD_HEIGHT && c >= 'A' && c < 'A' + FIELD_WIDTH));

            y = c-'A';
            x -= 1;
            system("cls");

            game.Move(x, y);
        }
        else
        {
            do
            {
                y = rand() % FIELD_HEIGHT;
                x = rand() % FIELD_WIDTH;
            } while (game.getNCurrF().getCell(y, x).getValue() == MISS || game.getNCurrF().getCell(y, x).getValue() == DESTROYED);

            game.Move(x, y);
        }

        std::cout << "   " << curr.getName() << " made a move " << (char)(y + 'A') << (x + 1) << '\n';
    }

    if (game.getNCurrF().countAlive() == 0)
    {
        system("cls");
        ShowFields();
        std::cout << '\n' << "   " << game.getCurrP().getName() << " wins " << '\n';
    }
}
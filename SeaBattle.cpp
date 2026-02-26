#include <iostream>
#include <random>
#include <time.h>
#include <locale.h>
#include <iomanip>
using namespace std;

struct cell
{
    char value = '.';
    bool hidden = true; // false для отладки
};

void ShowFields(cell field[12][12], cell enemyfield[12][12])
{
    cout << "           you           ";
    cout << "          enemy          ";
    cout << endl;

    cout << "   a b c d e f g h i j   ";
    cout << "   a b c d e f g h i j   ";
    cout << endl;

    for (int i=1; i<11; i++)
    {
        cout << setw(2) << i;
        for (int j=1; j<11; j++)
            cout << ' ' << field[i][j].value;

        cout << "   ";

        cout << setw(2) << i;
        for (int j=1; j<11; j++)
        {
            if (enemyfield[i][j].hidden == true)
                cout << ' ' << '.';
            else
                cout << ' ' << enemyfield[i][j].value;
        }
        cout << endl;
    }
}

void ClearField(cell anyfield[12][12])
{
    for (int i=0; i<12; i++)
    {
        for (int j=0; j<12; j++)
            anyfield[i][j].value = '.';
    }
}

void shift(int* M, int index, int n)
{
    int buffer = M[index];
    for (int i = index; i<n; i++)
        M[i] = M[i+1];
    M[n-1] = buffer;
}

bool isntXNearby(cell anyfield[12][12], int x, int y)
{
    for (int i = x-1; i < x+2; i++)
    {
        for (int j = y-1; j < y+2; j++)
            if (anyfield[i][j].value == 'O')
                return false;
    }
    return true;
}

bool CheckPlacement(cell anyfield[12][12], int x, int y, int length, int dir)
{
    if (length == 0)
        return true;

    if (x > 10 || x <= 0 || y > 10 || y <= 0)
        return false;
    if (!isntXNearby(anyfield, x, y))
        return false;

    if (dir == 0)
        x -= 1;
    else if (dir == 1)
        x += 1;
    else if (dir == 2)
        y -= 1;
    else if (dir == 3)
        y += 1;

    return CheckPlacement(anyfield, x, y, length-1, dir);
}

bool ShipPlacement(cell anyfield[12][12], int x, int y, int length, int dir)
{
    if (CheckPlacement(anyfield, x, y, length, dir))
    {
        for (int i=0; i<length; i++)
        {
            if (dir == 0)
                anyfield[x-i][y].value = 'O';
            else if (dir == 1)
                anyfield[x+i][y].value = 'O';
            else if (dir == 2)
                anyfield[x][y-i].value = 'O';
            else if (dir == 3)
                anyfield[x][y+i].value = 'O';
        }
        return true;
    }
    return false;
}

void ShipPlacementGenerator(cell anyfield[12][12])
{
    int dirs[] = { 0,1,2,3 }; //North, South, West, East

    int gc = 0; //generator counter
    for (gc; gc<1;)
    {
        int x = 1 + rand()%10;
        int y = 1 + rand()%10;
        for (int rc=0; rc<4; rc++)
        {
            int d = rand() % (4-rc);
            if (ShipPlacement(anyfield, x, y, 4, dirs[d]))
            {
                gc++;
                break;
            }
            shift(dirs, d, 4);
        }
    }

    for (int i=0; i<4; i++)
        dirs[i] = i;

    gc = 0;
    for (gc; gc<2;)
    {
        int x = 1 + rand()%10;
        int y = 1 + rand()%10;
        for (int rc=0; rc<4; rc++)
        {
            int d = rand() % (4-rc);
            if (ShipPlacement(anyfield, x, y, 3, dirs[d]))
            {
                gc++;
                break;
            }
            shift(dirs, d, 4);
        }
    }

    for (int i = 0; i < 4; i++)
        dirs[i] = i;

    gc = 0;
    for (gc; gc<3;)
    {
        int x = 1 + rand()%10;
        int y = 1 + rand()%10;
        for (int rc=0; rc<4; rc++)
        {
            int d = rand() % (4-rc);
            if (ShipPlacement(anyfield, x, y, 2, dirs[d]))
            {
                gc++;
                break;
            }
            shift(dirs, d, 4);
        }
    }

    gc = 0;
    for (gc; gc<4;)
    {
        int x = 1 + rand()%10;
        int y = 1 + rand()%10;
        if (isntXNearby(anyfield, x, y))
        {
            anyfield[x][y].value = 'O';
            gc++;
        }
    }
}

void Paint(cell anyfield[12][12],int x,int y, int length,int dir)
{
    int i = -1;
    if (dir == 0)
    {
        for (i; i<=length; i++)
        {
            anyfield[x+i][y-1].value = '*';
            anyfield[x+i][y-1].hidden = false;

            anyfield[x+i][y+1].value = '*';
            anyfield[x+i][y+1].hidden = false;
        }
        anyfield[x-1][y].value = '*';
        anyfield[x-1][y].hidden = false;

        anyfield[x+length][y].value = '*';
        anyfield[x+length][y].hidden = false;
    }
    else
    {
        for (i; i<=length; i++)
        {
            anyfield[x-1][y+i].value = '*';
            anyfield[x-1][y+i].hidden = false;

            anyfield[x+1][y+i].value = '*';
            anyfield[x+1][y+i].hidden = false;
        }
        anyfield[x][y-1].value = '*';
        anyfield[x][y-1].hidden = false;

        anyfield[x][y+length].value = '*';
        anyfield[x][y+length].hidden = false;
    }
}

void ShipDestroying(cell anyfield[12][12], int x, int y)
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if ( (i+j)%2 == 1 )
            {
                if (anyfield[x+i-1][y+j-1].value == 'O')
                    return;
            }
        }
    }

    int dir = 0;
    int length = 1;

    int startX = x;
    int startY = y;

    if ((anyfield[x-1][y].value=='X') || (anyfield[x+1][y].value == 'X'))
    {
        dir = 0;

        for (int i=1; anyfield[x-i][y].value == 'X' || anyfield[x-i][y].value == 'O'; i++)
            startX = x-i;

        int endX=x;
        for (int i=1; anyfield[x+i][y].value == 'X' || anyfield[x+i][y].value == 'O'; i++)
            endX = x+i;

        length = endX-startX + 1;
    }
    else if ((anyfield[x][y-1].value == 'X') || (anyfield[x][y+1].value == 'X'))
    {
        dir = 1;

        for (int i=1; anyfield[x][y-i].value == 'X' || anyfield[x][y-i].value == 'O'; i++)
            startY = y-i;

        int endY=y;
        for (int i=1; anyfield[x][y+i].value == 'X' || anyfield[x][y+i].value == 'O'; i++)
            endY = y+i;

        length = endY-startY + 1;
    }

    bool isDestroyed = true;
    for (int i=0; i<length; i++)
    {
        if (dir == 0)
        {
            if (anyfield[startX+i][y].value != 'X')
            {
                isDestroyed = false;
                break;
            }
        }
        else
        {
            if (anyfield[x][startY+i].value != 'X')
            {
                isDestroyed = false;
                break;
            }
        }
    }

    if (isDestroyed)
        Paint(anyfield, startX, startY, length, dir);
    return;
}

int CheckCell(cell anyfield[12][12], int x, int y)
{
    if (anyfield[x][y].value == 'O')
    {
        anyfield[x][y].hidden = false;
        anyfield[x][y].value = 'X';
        ShipDestroying(anyfield,x,y);
        return 2;
    }
    else if (anyfield[x][y].value == '.')
    {
        anyfield[x][y].hidden = false;
        anyfield[x][y].value = '*';
        return 1;
    }
    else
        return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int seed = time(NULL);
    srand(seed);

    cell field[12][12];

    for (int i=1; i<11; i++)
    {
        for (int j=1; j<11; j++)
            field[i][j].hidden = false;
    }

    cell enemyfield[12][12];

    cout << "----- Морской бой -----" << endl;
    cout << endl;
    cout << "На данный момент доступно только случайное расположение кораблей, введи r чтобы начать. ";
    char start = ' ';
    while (start != 'r')
        cin >> start;
    cin.ignore();

    int alive;
    int enemyalive;
    int turn;

    char q = 'n'; // quit

    // Ввод
    char c;
    int x;
    int y;

    int changing;

    while (q != 'y')
    {
        turn = 0;
        alive = 20;
        enemyalive = 20;

        system("cls");

        ClearField(field);
        ClearField(enemyfield);

        ShipPlacementGenerator(field);
        ShipPlacementGenerator(enemyfield);

        for (int i=1; i<11; i++)
        {
            for (int j=1; j<11; j++)
                enemyfield[i][j].hidden = true;
        }

        while (alive != 0 and enemyalive != 0)
        {
            if (turn%2 == 0)
            {
                ShowFields(field, enemyfield);
                do
                {
                    cout << endl << "   Ваш ход: ";
                    cin >> c >> x;

                    if (!cin)
                    {
                        cin.clear();
                        cin.ignore(10000,'\n');
                        c = ' ';
                        x = 0;
                    }
                } while (x > 10 || x <= 0 || c > 'j' || c < 'a');

                y = c - 96;

                system("cls");

                changing = CheckCell(enemyfield, x, y);
                if (changing == 2)
                    enemyalive -= 1;
                turn += changing;
            }
            if (turn%2 == 1)
            {
                x = 1 + rand()%10;
                y = 1 + rand()%10;

                changing = CheckCell(field, x, y);
                if (changing == 2)
                    alive -= 1;
                turn += changing;
                if (changing != 0)
                    cout << "   Бот сходил " << (char)(y+96) << " " << x << endl << endl;
            }
        }

        if (alive == 0)
        {
            system("cls");
            ShowFields(field, enemyfield);
            cout << endl << "   YOU LOSE!!! ";
        }
        else if (enemyalive == 0)
        {
            system("cls");
            ShowFields(field, enemyfield);
            cout << endl << "   YOU WIN!!! ";
        }

        cout << "Quit? y/n ";
        while (q!='y' && q!='n')
            cin >> q;
    }
    return 0;
}
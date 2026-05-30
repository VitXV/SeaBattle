#include <iostream>
#include <string>
#include "SeaBattle.h"
#include "Interface.h"

using namespace std;

int main()
{
    srand(time(NULL));

    Human pl1("Player1");
    Computer pl2("Optimus Prime Decepticon lvl 99999");

    SeaBattle test(pl1,pl2);
    Console interface(test);

    interface.play();

    return 0;
}

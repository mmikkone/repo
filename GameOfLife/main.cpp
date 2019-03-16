#include <iostream>
#include "gametable.h"
#include "winconsoleui.h"

using namespace std;

int main()
{
    GameTable gametable(new WinConsoleUI);

    gametable.play();

    return 0;
}

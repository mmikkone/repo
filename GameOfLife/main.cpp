#include <iostream>
#include "gametable.h"
#include "winconsoleui.h"

using namespace std;

int main()
{
    shared_ptr<WinConsoleUI> ui(new WinConsoleUI);

    GameTable gametable(ui);

    gametable.play();

    return 0;
}

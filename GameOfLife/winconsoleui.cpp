#include <iostream>
#include <conio.h>
#include <limits>
#include "winconsoleui.h"

void WinConsoleUI::saveCursorPosition()
{
    xsave = x;
    ysave = y;
}

void WinConsoleUI::restoreCursorPosition()
{
    x = xsave;
    y = ysave;
    setCursorPosition(x, y);
}

WinConsoleUI::WinConsoleUI(): x(0), y(0){}

WinConsoleUI::~WinConsoleUI(){}

bool WinConsoleUI::redrawTable()
{
    clearScreen();
    saveCursorPosition();
    for(uint8_t i = 0; i < table->size(); i++)
    {
        for(uint8_t j = 0; j < (*table)[i].size(); j++)
        {
            setCursorPosition(i,j);
            if((*table)[i][j]) cout << 'x';
            else cout << ' ';
        }
        cout << endl;
    }
    cout << message;
    restoreCursorPosition();

    return true;
}

void WinConsoleUI::showMessage(const string& msg)
{
    message = msg;
    redrawTable();
}

bool WinConsoleUI::init(const vector<vector<bool> > &table)
{
    this->table = &table;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    return SetConsoleCursorPosition(console,pos);
}

bool WinConsoleUI::getGameTableSize(uint8_t &width, uint8_t &height)
{
    int w, h;

    cin >> w >> h;

    string old_msg = message;

    while(cin.fail() || w < 0 || w > UINT8_MAX || h < 0 || h > UINT8_MAX)
    {
        showMessage("Width and height must be between 0 and 255.\n");
        cin.clear(); //clear fail flag
        cin.ignore(10000, '\n'); //TODO numeric_limits<streamsize>::max() didn't work???
        cin >> w >> h;
    }

    showMessage(old_msg);

    width = static_cast<uint8_t>(w);
    height = static_cast<uint8_t>(h);
    return true;
}

bool WinConsoleUI::getChoice(uint8_t &choice)
{
    choice = static_cast<uint8_t>(_getch());
    return true;
}

bool WinConsoleUI::getChoiceNonBlock(uint8_t &choice)
{
    DWORD old_mode, mode, n;
    INPUT_RECORD buf[1];

    HANDLE h_stdin = GetStdHandle(STD_INPUT_HANDLE);
    if (h_stdin == INVALID_HANDLE_VALUE) return false;

    if (! GetConsoleMode(h_stdin, &old_mode) ) return false;

     // Enable the window and mouse input events.
     mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
     if (! SetConsoleMode(h_stdin, mode) ) return false;

     if(!GetNumberOfConsoleInputEvents(h_stdin, &n)) return false;

     if(!n) //nothing to read -> return immediately
     {
         SetConsoleMode(h_stdin, old_mode);
         return false;
     }

     if(!ReadConsoleInput(h_stdin, buf, 1, &n)) return false;

    if(buf[0].EventType == KEY_EVENT) choice = static_cast<uint8_t>(buf[0].Event.KeyEvent.uChar.AsciiChar);
    else return false;

    SetConsoleMode(h_stdin, old_mode);

    return true;
}

bool WinConsoleUI::setCursorPosition(uint8_t x, uint8_t y)
{
    if(!table->size())
        return false;
    else if(!(*table)[0].size())
        return false;

    if( x >= table->size() || y >= (*table)[0].size() ) return false;

    COORD pos = {x, y};
    bool ret;
    if( (ret = SetConsoleCursorPosition(console,pos)) )
    {
        this->x = x;
        this->y = y;
    }
    return ret;
}

bool WinConsoleUI::clearScreen()
{
    COORD topLeft  = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    return SetConsoleCursorPosition(console, topLeft);
}

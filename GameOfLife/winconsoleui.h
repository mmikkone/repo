#ifndef WINCONSOLEUI_H
#define WINCONSOLEUI_H

#include <Windows.h>
#include <string>
#include <vector>
#include "ui.h"

using namespace std;

/**
 * @brief Windows console/command prompt user interface for Game of Life.
 */
class WinConsoleUI: public UI
{
private:
    uint8_t x, y;                       //cursor coordinates
    uint8_t xsave, ysave;               //saved cursor coordinates
    HANDLE console;                     //Handle to the console. Windows specific.
    const vector<vector<bool> >* table; //Pointer to the table which tells if cells are dead or alive.
    string message;                     //message to user

    void saveCursorPosition();          //saves cursor position
    void restoreCursorPosition();       //restores cursor position

public:
    WinConsoleUI();
    virtual ~WinConsoleUI();

    virtual bool init(const vector<vector<bool> >& table);
    virtual bool getGameTableSize(uint8_t& width, uint8_t& height);
    virtual bool getChoice(uint8_t& choice);
    virtual bool getChoiceNonBlock(uint8_t& choice);
    virtual bool clearScreen();
    virtual bool redrawTable();
    virtual void showMessage(const string& msg);
    virtual bool setCursorPosition(uint8_t x, uint8_t y);
};

#endif // WINCONSOLEUI_H

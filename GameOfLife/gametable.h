#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <iostream>
#include <string>
#include "winconsoleui.h"

using namespace std;

/**
 * @brief The game table class
 *
 * Contains game logic. Just construct with UI and call play().
 */
class GameTable
{
private:
    unique_ptr<UI> ui;                                  //Pointer to UI.
    uint8_t x, y;                                       //Cursor coordinates
    bool initialized = false;                           //Is UI initialized?
    vector<vector<bool> > table;                        //Game table. If cell is alive, it's value is true;

    void cursorUp();                                    //Moves cursor on the game table.
    void cursorDown();                                  //Moves cursor on the game table.
    void cursorForward();                               //Moves cursor on the game table.
    void cursorBackward();                              //Moves cursor on the game table.
    uint8_t getNumNeighbours(uint8_t x, uint8_t y);     //Gets number of live neighbours of a cell.
    void clear();                                       //Clears up everything.
    void fill();                                        //Lets the user fill the game table.
    void runStep();                                     //Runs a single step/iteration.

public:

    /**
     * @brief Constructs GameTable and takes ownership of UI*.
     */
    GameTable(UI*);

    /**
     * @brief Plays the game.
     */
    void play();                                        //Play the game.
};

#endif // TABLE_H

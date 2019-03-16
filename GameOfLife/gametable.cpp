#include "gametable.h"
#include <conio.h>
#include <Windows.h>
#include <chrono>
#include <thread>

GameTable::GameTable(UI* ui):
    ui(ui),
    x(0),
    y(0)
{
}

void GameTable::cursorUp()
{
    if(y) y--;
    ui->setCursorPosition(x,y);
}

void GameTable::cursorDown()
{
    if(y<(table[x].size()-1)) y++;
    ui->setCursorPosition(x,y);
}

void GameTable::cursorForward()
{

    if(x < (table.size()-1) ) x++;
    ui->setCursorPosition(x,y);
}

void GameTable::cursorBackward()
{
    if(x) x--;
    ui->setCursorPosition(x,y);
}

void GameTable::fill()
{
    uint8_t w = 0, h = 0;
    uint8_t choice = 0;

    clear();

    ui->showMessage("Give table width and height.\n");
    if(!ui->getGameTableSize(w, h)) return;
    table.resize(w);
    for(auto& i: table) i.resize(h, false);

    do
    {
        ui->showMessage("Move with A,S,D and W keys, use T to toggle cells.\nFinish with dot (.).");
        if(!ui->getChoice(choice)) return;

        switch (choice)
        {
        case 'a':
        case 'A':
        {
            cursorBackward();
            break;
        }
        case 'd':
        case 'D':
        {
            cursorForward();
            break;
        }
        case 's':
        case 'S':
        {
            cursorDown();
            break;
        }
        case 'w':
        case 'W':
        {
            cursorUp();
            break;
        }
        case 't':
        case 'T':
        {
            table[x][y] = !table[x][y]; //toggle alive
            break;
        }
        }
    }while(choice != '.');

    ui->setCursorPosition(0,0);
    ui->clearScreen();
}

void GameTable::clear()
{
    x = y = 0;
    table.clear();
    ui->clearScreen();
}

uint8_t GameTable::getNumNeighbours(uint8_t x, uint8_t y)
{
    if(x>=table.size() || y>=table[0].size()) return 0;

    uint8_t num,xmin,xmax,ymin,ymax;

    num = 0;

    x>0 ? xmin=x-1 : xmin=x;
    y>0 ? ymin=y-1 : ymin=y;
    x<(table.size()-1) ? xmax=x+1 : xmax=x;
    y<(table[0].size()-1) ? ymax=y+1 : ymax=y;

    for(unsigned int i = xmin; i<=xmax; i++)
    {
        for(unsigned int j = ymin; j<=ymax; j++)
        {
            if(table[i][j]) num++;
        }
    }

    if(table[x][y]) num--;

    return num;
}

void GameTable::runStep()
{
    vector<vector<bool> > copy;

    copy.resize(table.size());
    for(auto& i: copy) i.resize(table[0].size(), false);

    uint8_t n;

    for(uint8_t i = 0; i<table.size(); i++)
    {
        for(uint8_t j = 0; j<table[i].size(); j++)
        {
            n = getNumNeighbours(i,j);

            if(table[i][j]) //cell alive
            {
                if(n==2 || n==3)
                {
                    copy[i][j] = true;
                }
            }
            else //cell dead
            {
                if( n==3 ) copy[i][j] = true;
            }
        }
    }

    table = copy;

    ui->redrawTable();

    this_thread::sleep_for(std::chrono::milliseconds(200));
}

void GameTable::play()
{
    try
    {

        uint8_t choice = 0;

        if(!initialized) ui->init(table);

        do
        {
            fill();

            ui->showMessage("Press \'s\' to play step-by-step or \'c\' to play continuously.\nPress dot (.) to quit.");

            do
            {
                if(!ui->getChoice(choice)) return;

                switch (choice)
                {
                case 's':
                case 'S':
                {
                    runStep();
                    break;
                }
                case 'c':
                case 'C':
                {
                    while(choice != '.' && choice != 's' && choice != 'S')
                    {
                        runStep();
                        ui->getChoiceNonBlock(choice);
                    }
                    break;
                }
                }
            }while(choice != '.');


            ui->showMessage("Play again (y/n)?");

            do
            {
                if(!ui->getChoice(choice)) return;

            }while(choice != 'y' && choice != 'n');

        }while(choice == 'y');

        ui->clearScreen();

    }
    catch (const exception& e)
    {
        ui->showMessage(e.what());
    }
}

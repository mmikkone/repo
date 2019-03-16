#ifndef UI_H
#define UI_H

#include <vector>
#include <memory>

using namespace std;

/**
 * @brief The UI class is the base class for all Game of Life UIs.
 */
class UI
{
public:
    UI();
    virtual ~UI();

    /**
     * @brief Initializes UI
     * @param table Contains booleans which tell if the cell is alive (true) or dead (false)
     * @return True if initialization is a success or false if not.
     */
    virtual bool init(const vector<vector<bool> >& table) = 0;

    /**
     * @brief Gets the game table size from the user.
     * @param width Width of the game table.
     * @param height Height of the game table.
     * @return True if succeeds, false if not.
     */
    virtual bool getGameTableSize(uint8_t& width, uint8_t& height) = 0;

    /**
     * @brief Prompts user for input (e.g. key press).
     * @param choice The returned choice.
     * @return True if succeeds, false if not.
     */
    virtual bool getChoice(uint8_t& choice) = 0;

    /**
     * @brief Prompts user for input, but doesn't block execution (e.g. key press).
     * @param choice The returned choice.
     * @return True if there's input, false if not there's no input or something went wrong.
     */
    virtual bool getChoiceNonBlock(uint8_t& choice) = 0;

    /**
     * @brief Clears the UI.
     * @return True if succeeds, false if not.
     */
    virtual bool clearScreen() = 0;

    /**
     * @brief Redraws/updates the game table.
     * @return True if succeeds, false if not.
     */
    virtual bool redrawTable() = 0;

    /**
     * @brief Shows a message to the user.
     * @param msg The message.
     */
    virtual void showMessage(const string& msg) = 0;

    /**
     * @brief Sets the cursor position on the game table.
     * @param x X coordinate of the game table.
     * @param y Y coordinate of the game table.
     * @return True if succeeds, false if not.
     */
    virtual bool setCursorPosition(uint8_t x, uint8_t y) = 0;
};

#endif // UI_H

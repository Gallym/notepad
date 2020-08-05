/**
 * @class Notepad
 * @brief Main application class.
 * This class creates windows and manages switching between them.
 */

#ifndef NOTEPAD
#define NOTEPAD

#include <ncurses.h>

#include "windows/MyWindow.h"
#include "windows/SearchWindow.h"
#include "windows/NotesWindow.h"
#include "windows/PreviewWindow.h"

using namespace std;

class Notepad {
public:

    /** 
     * Constructor for Notepad.
     */
    Notepad();

    /** 
     * Destructor for Notepad.
     */
    ~Notepad();

    /** 
     * Main method to start application Notepad.
     */
    void run();
private:
    int currWinId; /**< current window id. */
    MyWindow * windows[3]; /**< Array of pointers to main wwindows. */
};

#endif
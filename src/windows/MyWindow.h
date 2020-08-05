/**
 * @class MyWindow
 * @brief Parent class for all Windows.
 * This class describes main behavior of every Window. 
 * Main logic is implemented here.
 * Also provided auxiliary methods for plesant work in derived classes.
 */

#ifndef MYWINDOW
#define MYWINDOW

#include "../notes/Note.h"
#include "Content.h"

#include <ncurses.h>

#include <string>
#include <vector>

using namespace std;

class MyWindow {
public:

    /** 
     * Constructor for MyWindow.
     */
    MyWindow(int height, int width, int startY, int startX, WINDOW * optWindow, string name, vector<string> opts);
     
    /** 
     * Destructor for MyWindow.
     */
    virtual ~MyWindow();

    /** 
     * Initialize ncurses window.
     */
    virtual void init();
    
    /**
     * Activates window and implements main functionality of window.
     * Here User uses functionality of window by selecting specific option(s).
     */
    virtual void activate(); 

    /**
     * @returns isExit value.
     */
    virtual bool getIsExit();
protected:
    static const unsigned ENTER      = 10;   /**< Constant for Enter key. */
    static const unsigned BACK_SPACE = 127;  /**< Constant for Back space key. */
    static const char     TAB        = '\t'; /**< Constant for Tab key. */
    static const char     PREVIEW    = 'p';  /**< Constant for Preview command. */
    static const char     QUIT       = 'q';  /**< Constant for Quit command. */

    WINDOW * window; /**< Pointer to NCurses Window. */
    int height; // TODO remove
    int width;
    int startY;
    int startX; 
    
    WINDOW * optWindow; /**< Pointer to Options Window. */
    string name; /**< Name of Window. */
    string title; /**< Title of Window. Changes depending on option which is being executed. */
    const vector<string> options; /**< Options which can be selected and executed. */
    int currOpt; /**< Current option selected by user and to be executed */
    Content content; /**< Content to be displayed inside Window */

    bool isExit; /**< Flag to be detected by Notepad for exiting program */

    /** 
     * Deactivates window: printes first page of MyWindow::content 
     * and sets standart color of borders. 
     */
    virtual void deactivate();

    /** 
     * Asks User if they want to exit program.
     * In positive case sets MyWindow::isExit as true.
     */
    virtual bool exit();
    
    /** 
     * Executes current chosen option.
     * Has to be implemented for each derived class.
     */
    virtual void execCurrOpt() = 0;

    /**
     * Gets Users input from Options Window. 
     */
    virtual string readInput() const;

    /** 
     * Clears Window.
     */
    virtual void clear() const;
    
    /** 
     * Prints out MyWindow::options into MyWindow::optWindow.
     */
    virtual void printOptions() const;

    /** 
     * Prints specific options of Window if needed. 
     */
    void printThisOptions(const vector<string> opt) const;
    
    /** 
     * Clears Options Window 
     */
    virtual void clearOptions() const;
    
    /** 
     * Updates title of window 
     */
    virtual void updateTitle(string title) const;
    
    /** 
     * Prints out first page of MyWindow::content 
     */
    virtual void printContent();

    /** 
     * Higlights borders of window 
     */
    virtual void colorBorders() const;

    /** 
     * Removes higlighting of window
     */
    virtual void uncolorBorders() const;

};

#endif
#include "Notepad.h"

using namespace std;


Notepad::Notepad() : currWinId(0) {
    printw("My awesome NOTEPAD");
    refresh();

    // getting size of screen 
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    // options vars
    int optionsHeight   = 3;
    int optionsWidth  = xMax;
    int optionsYStart = 1;
    int optionsXStart = 0;
    // search vars
    int searchHeight = yMax - optionsHeight - optionsYStart;
    int searchWidth  = xMax/4;
    int searchYStart = optionsHeight + optionsYStart;
    int searchXStart = 0;
    // files vars
    int filesHeight = yMax - optionsHeight - optionsYStart;
    int filesWidth  = xMax/4;
    int filesYStart = optionsHeight + optionsYStart;
    int filesXStart = searchWidth;
    // preview vars
    int previewHigh   = yMax - optionsHeight - optionsYStart;
    int previewWidth  = xMax/2;
    int previewYStart = optionsHeight + optionsYStart;
    int previewXStart = searchWidth + filesWidth;

    // creating Option window
    WINDOW * optionsWin = newwin(optionsHeight, optionsWidth, optionsYStart, optionsXStart);
    box(optionsWin, 0, 0);
    mvwprintw(optionsWin, 0, 5, " Options: [Search]");
    wrefresh(optionsWin);

    // creating main windows and adding them to array
    PreviewWindow * prWin = new PreviewWindow(previewHigh,  previewWidth, previewYStart, previewXStart, optionsWin, "Preview");
    NotesWindow   * fWin  = new NotesWindow  (filesHeight,  filesWidth,   filesYStart,   filesXStart,   optionsWin, prWin, "Files");
    windows[0] =            new SearchWindow (searchHeight, searchWidth,  searchYStart,  searchXStart,  optionsWin, "Search", fWin);
    windows[2] = prWin;
    windows[1] = fWin;
}

Notepad::~Notepad() {
    delete windows[0];
    delete windows[1];
    delete windows[2];
}

void Notepad::run() {
    while(1) {
        windows[currWinId]->activate();
        if (windows[currWinId]->getIsExit()) break; // exit applicatino
        if (++currWinId > 2) { currWinId = 0; } // if last window switch to first
    }
}
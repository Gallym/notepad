#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "Notepad.h"

using namespace std;

// Initializes the curses.h
bool curses_init() {
    initscr();
    noecho();
    cbreak();
    if (has_colors()) {
        use_default_colors();
        start_color();
        init_pair(1, COLOR_WHITE, -1);
        init_pair(2, COLOR_RED, -1);
    } else {
        cout<<"u have no colors, sorry"<<endl;
        return false;
    }
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    return yMax>20 && xMax>80; 
}

int main (int argc, char** argv) {
    // start ncurses
    if (!curses_init()) {
        endwin();
        cerr<<"Your screen is too small. Make it at least 80x20. Buy."<<endl;
        return 1;
    }

    Notepad notepad;
    notepad.run();

    // exit ncurses
    endwin();

    return 0;
}
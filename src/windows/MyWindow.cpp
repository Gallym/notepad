#include "MyWindow.h"

MyWindow::MyWindow(int height, int width, int startY, int startX, WINDOW * optWindow, string name, vector<string> opts) : 
                                            height(height),
                                            width(width),
                                            startY(startY),
                                            startX(startX),
                                            optWindow(optWindow),
                                            name(name),
                                            options(opts),
                                            currOpt(0),
                                            isExit(false) { 
    init(); 
}

MyWindow::~MyWindow() { 
    delwin(window); 
}

void MyWindow::init() {
    window = newwin(height, width, startY, startX);
    box(window, 0, 0);
    mvwprintw(window, 0, 1, name.c_str());
    wrefresh(window);
    content = Content(window, height - 2, width - 2);
}

void MyWindow::activate() {
    clearOptions();
    currOpt = 0;
    int currKey;
    while(1) {  
        keypad(optWindow, true);
        printOptions();
        printContent();
        
        currKey = wgetch(optWindow);
        refresh();
        switch (currKey) {
            case KEY_LEFT:
                if (--currOpt < 0) currOpt = 0;
                break;
            case KEY_RIGHT:
                if (++currOpt >= (int)options.size()) {  currOpt = options.size() - 1; }
                break;
            case TAB:
                currOpt = 0;
                deactivate();
                return;
            case QUIT:
                if (exit()) return;
                break;
            case ENTER:
                execCurrOpt();
                break;
            default:
                break;
        }
        
        wrefresh(optWindow);
        refresh();
    }
}

/**************** Protected methods ***********/

bool MyWindow::getIsExit() {
    return isExit;
}

void MyWindow::deactivate() {
        printContent();
        uncolorBorders();
}

bool MyWindow::exit() {
    werase(optWindow);  
    box(optWindow, 0, 0);
    refresh();
    mvwprintw(optWindow, 1, 1, ("Do you want to exit? type 'y' if YES or any other letter if NO"s).c_str());
    wrefresh(optWindow);
    wmove(optWindow, 1, 74);
    keypad(optWindow, true);
    char ch = wgetch(optWindow);
    return isExit = (ch == 'y');
}

string MyWindow::readInput() const {
    clearOptions();
    wmove(optWindow, 1, 1);
    keypad(optWindow, true);
    string inputStr;
    char ch;
    bool enterF = false;
    while (1) {
        ch = wgetch(optWindow);

        // if ENTER pressed twice return
        if (enterF) break;

        switch (ch) {
        case ENTER: // ENTER KEY
            if (!enterF) enterF = true; // ENTER pressed once
            break;
        case BACK_SPACE: // BACK_SPACE
            inputStr = inputStr.substr(0, inputStr.size()-1);
            enterF = false;
            clearOptions();
            break;
        default:
            inputStr+=ch;
            enterF = false;
            break;
        }
        mvwprintw(optWindow, 1, 1, inputStr.c_str());
        wrefresh(optWindow);

        //if (ch == 10) break; // uncomment to remove double ENTER 
    }

    return inputStr;
}

void MyWindow::clear() const {
    werase(window);
    box(window, 0, 0);
    refresh();
    mvwprintw(window, 0, 1, (name + (title == "" ? "" : (" [" + title + "] "))).c_str());
    wrefresh(window);
    colorBorders();
}

void MyWindow::clearOptions() const {
    werase(optWindow);  
    box(optWindow, 0, 0);
    refresh();
    mvwprintw(optWindow, 0, 5, (string(" Options: ") + "[" + name + "] ").c_str());
    wrefresh(optWindow);
}

void MyWindow::updateTitle(string title) const {
    colorBorders();
    mvwprintw(window, 0, 1, (" " + name + " [" + title + "]: ").c_str());
    wrefresh(window);
}

void MyWindow::printContent() {
    content.printCurrentPage(-1);
    colorBorders();
}

void MyWindow::printOptions() const {
    clearOptions();
    int curX = 1;
    for (int i = 0; i < (int)options.size(); i++) {
        wmove(optWindow, 1, curX);
        if (i == currOpt) wattron(optWindow, A_REVERSE);
        wprintw(optWindow, options[i].c_str());
        wattroff(optWindow, A_REVERSE);
        curX += options[i].size() + 2;
    }

    wrefresh(optWindow);
}

void MyWindow::printThisOptions(const vector<string> opt) const {
    clearOptions();
    int curX = 1;
    for (int i = 0; i < (int)opt.size(); i++) {
        wmove(optWindow, 1, curX);
        if (i == currOpt) wattron(optWindow, A_REVERSE);
        wprintw(optWindow, opt[i].c_str());
        wattroff(optWindow, A_REVERSE);
        curX += opt[i].size() + 1;
    }
    wrefresh(optWindow);
}

void MyWindow::colorBorders() const {
    wattron(window,COLOR_PAIR(2));
    box(window,0,0);
    wrefresh(window);
    wattroff(window, COLOR_PAIR(2));
    mvwprintw(window, 0, 1, (name + ":").c_str());
    wrefresh(window);
}

void MyWindow::uncolorBorders() const {
    box(window,0,0);
    wrefresh(window);
    mvwprintw(window, 0, 1, (name + ":").c_str());
    wrefresh(window);
}
#include "Content.h"

Content::Content() {}

Content::Content(WINDOW * window, int height, int width) : window(window), maxHeight(height), maxWidth(width), currPage(0) {
    pages.emplace_back(vector<string>());
}

int Content::getMaxWidth() const {
    return maxWidth;
}

int Content::getMaxHeight() const {
    return maxHeight;    
}

int Content::getCurrentPageSize() const {
    return pages[currPage].size();
}

int Content::getCurrentPageNumber() const {
    return currPage;
}

void Content::addLine(string wholeLine) {
    vector<string> lines;
    istringstream iss(wholeLine);
    string realLine; 
    string subLine;
    while (getline(iss, realLine)) {
        do {
            if (pages.size() == 0 || pages.back().size() >= (unsigned)maxHeight) {
                pages.push_back(vector<string>());
            }

            // cut sub line from whole line if bigger
            if (realLine.length() > (unsigned)maxWidth) {
                subLine  = realLine.substr(0, maxWidth);
                realLine = realLine.substr(maxWidth);
            } else {
                subLine  = realLine;
                realLine = "";
            }
            // add line to the last Page
            pages.back().emplace_back(subLine);
        } while (realLine.length() > 0);
    }
}

void Content::addPair(string left, string right) {
    if ((int)left.length() > maxWidth/2) {
        left = left.substr(0, maxWidth/2);
    }
    if ((int)right.length() > maxWidth/2) {
        right = right.substr(0, maxWidth/2);
    }
    left += string(maxWidth/2 - left.length(), '.');
    addLine(left + right);
}

void Content::addStripe() {
    addLine(string(maxWidth, '_'));
}

void Content::clearContent() {
    pages.clear();
}

void Content::printError(string errorMsg) {
    clear();
    mvwprintw(window, 0, 2, " ERROR ");
    mvwprintw(window, 1, 1, "Press any key to continue.");
    mvwprintw(window, 2, 1, errorMsg.c_str());
    wrefresh(window);
    wgetch(window);
    printCurrentPage(-1);
}

void Content::printFirstPage(int linePos) {
    currPage = 0;
    printCurrentPage(linePos);
}

void Content::printCurrentPage(int linePos) const {
    clear();
    if (pages.empty() || pages[currPage].empty()) {
        return;
    }
    for (unsigned i = 0; i < pages[currPage].size(); i++) {
        if ((int)i == linePos) wattron(window, A_REVERSE);
        mvwprintw(window, i + 1, 1, pages[currPage][i].c_str());
        wattroff(window, A_REVERSE);
    }
    wrefresh(window);
}

void Content::printNextPage(int linePos) {
    if (currPage >= (int)pages.size() - 1) { // if last page
        currPage = pages.size() - 1;
        return;
    }

    currPage++;
    clear();
    for (unsigned i = 0; i < pages[currPage].size(); i++) {
        if ((int)i == linePos) wattron(window, A_REVERSE);
        mvwprintw(window, i + 1, 1, pages[currPage][i].c_str());
        wattroff(window, A_REVERSE);
    }
    wrefresh(window);
}

void Content::printPreviousPage(int linePos) {
    if (currPage <= 0) { // if last page
        currPage = 0;
        return;
    }

    currPage--;
    clear();
    for (unsigned i = 0; i < pages[currPage].size(); i++) {
        if ((int)i == linePos) wattron(window, A_REVERSE);
        mvwprintw(window, i + 1, 1, pages[currPage][i].c_str());
        wattroff(window, A_REVERSE);
    }
    wrefresh(window);
}

void Content::clear() const {
    werase(window);
    colorBorders();
    wrefresh(window);
    refresh();
}

void Content::colorBorders() const {
    wattron(window,COLOR_PAIR(2));
    box(window,0,0);
    wrefresh(window);
    wattroff(window, COLOR_PAIR(2));
}
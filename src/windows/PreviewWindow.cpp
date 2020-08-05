#include "PreviewWindow.h"

PreviewWindow::PreviewWindow(int height, int width, int startY, int startX, WINDOW * optWindow, string name) :
               MyWindow(height, width, startY, startX, optWindow, name, {"Preview", "Help"}), 
               previewNote(nullptr) {}

Note * PreviewWindow::getPreviewNote() const {
    return previewNote;
}

void PreviewWindow::setAndPrintPreviewNote(Note * note) {
    previewNote = note;
    content.clearContent();
    if (previewNote != nullptr) previewNote->fillContent(&content);
    content.printFirstPage(-1);
    uncolorBorders();
}

void PreviewWindow::previewMode() {
    if (previewNote == nullptr) {
        content.printError("Note was not selected!");
        return;
    }

    updateTitle("Preview Note");
    
    content.clearContent();
    previewNote->fillContent(&content);
    content.printFirstPage(-1);

    currOpt = 0;
    int currKey = 0;
    keypad(optWindow, true);
    while(1) {
        printThisOptions(prevOpt);
        
        currKey = wgetch(optWindow);
        refresh();
        switch (currKey) {
            case KEY_LEFT:
                if (--currOpt < 0) currOpt = 0;
                break;
            case KEY_RIGHT:
                if (++currOpt >= (int)prevOpt.size()) {  currOpt = prevOpt.size() - 1; }
                break;
            case ENTER: 
                switch (currOpt) {
                case 0: { // prev page
                    content.printPreviousPage(-1);
                    break;
                } case 1: { // next page
                    content.printNextPage(-1);
                    break;
                } default: { break; }
                }
                break;
            case QUIT:
                content.printFirstPage(-1);
                currOpt = 0;
                return;
                break;  
            default:
                break;
        }
        
        wrefresh(optWindow);
        refresh();
    }
}
void PreviewWindow::printHelp() {
    content.clearContent();
    content.addLine("Use TAB to move to next window");
    content.addLine("Use 'p' to show Note in Preview Window");
    content.addLine("Use 'q' to quit");
}

void PreviewWindow::execCurrOpt() {
    switch (currOpt) {
    case PREVIEW_MODE:
        previewMode();
        break;
    case HELP_MODE:
        printHelp();
        break;
    default:
        break;
    }
}

void PreviewWindow::printContent() {
    if (previewNote != nullptr) {
        content.clearContent();
        previewNote->fillContent(&content);
    }
    content.printFirstPage(-1);
    colorBorders();
}

void PreviewWindow::clearPreview() const {
    werase(window);
    box(window, 0, 0);
    refresh();
    mvwprintw(window, 0, 1, " Preview:");
    wrefresh(window);
}
/**
 * @class PreviewWindow
 * @brief Derived class from MyWindow for searching notes.
 * This class implements and extends functionality of parent MyWindow. 
 * PreviewWindow class introduces Window for preview notes.
 * User view Note and list over its pages.
 */

#ifndef PREVIEW_WINDOW
#define PREVIEW_WINDOW

#include <ncurses.h>
#include <string>
#include <vector>
#include "MyWindow.h"
#include "../notes/Note.h"

class PreviewWindow : public MyWindow {
public:

    /** 
     * Constructor for PreviewWindow.
     */
    PreviewWindow(int height, int width, int startY, int startX, WINDOW * optWindow, string name);
    
    /** 
     * Destructor for PreviewWindow.
     */
    virtual ~PreviewWindow() = default;

    /** 
     * @returns Note which is in preview at the moment.
     */
    Note * getPreviewNote() const;

    /** 
     * Sets given @param note as PreviewWindow::previewNote and prints it out.
     */
    void setAndPrintPreviewNote(Note * note);

    /** 
     * Clears out preview.
     */
    void clearPreview() const;

private:
    static const unsigned PREVIEW_MODE = 0; /**< Constant for Preview mode. */
    static const unsigned HELP_MODE    = 1; /**< Constant for Help mode. */

    Note * previewNote; /**< Note to be shown in preview. */

    const vector<string> prevOpt = {"Prev page", "Next page"}; /**< Auxiliary options for work with preview. */

    /** 
     * Implementation of MyWindow::execCurrOpt
     * Executes current chosen option (Preview, Help).
     * Also paging options are supported for viewing Note.
     */
    virtual void execCurrOpt();

    /** 
     * Overrides MyWindow::printContent.
     * Prints out first page of PreviewWindow::previewNote is presented.
     */
    virtual void printContent();

    /** 
     * Method to preview of PreviewWindow::previewNote and list over its pages.
     */
    void previewMode();

    /** 
     * Method to print help.
     */
    void printHelp(); 
};

#endif
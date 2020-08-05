/**
 * @class NotesWindow
 * @brief Derived class from MyWindow for searching notes.
 * This class implements and extends functionality of parent MyWindow. 
 * NotesWindow class introduces Window for work with notes.
 * User can import new notes and delete imported notes.
 * User can also select specific note and open it in PreviewWindow.
 * @see PreviewWindow.
 */

#ifndef NOTES_WINDOW
#define NOTES_WINDOW

#include <ncurses.h>
#include <string>
#include <vector>
#include <iostream>

#include "MyWindow.h"
#include "PreviewWindow.h"

#include "../notes/Note.h"
#include "../notes/BasicNote.h"
#include "../notes/CheckListNote.h"
#include "../notes/PriceListNote.h"

using namespace std;

class NotesWindow : public MyWindow {
public:
    /** 
     * Constructor for NotesWindow.
     */
    NotesWindow(int height, int width, int startY, int startX, WINDOW * optWindow, PreviewWindow * prevWin, string name);

    /** 
     * Destructor for NotesWindow.
     */
    virtual ~NotesWindow();

    /** 
     * @returns pointers to all imported notes.
     */
    vector<Note *> getNotes() const;

private:

    static const unsigned SELECT_MODE = 0; /**< Constant for Select mode. */
    static const unsigned IMPORT_MODE = 1; /**< Constant for Import mode. */
    static const unsigned DELETE_MODE = 2; /**< Constant for Delete mode. */
    
    ifstream input; /**< Input stream to read from the file. */
    PreviewWindow * prevWindow; /**< Pointer to PreviewWindow to show selected or imported Note. */
    vector<Note *> allNotes;  /**< Vector of pointers to all imported notes. */
    
    /** 
     * Implementation of MyWindow::execCurrOpt
     * Executes current chosen option (Select, Import, Delete).
     * Also paging options are supported for viewing and listing throughout all notes.
     */
    virtual void execCurrOpt();

    /**
     * Method to choose note 
     */
    Note * selectMode();

    /**
     * Method to import note via filepath 
     */
    Note * importMode();

    /**
     *  Method to delete note from Notepad 
     */
    void deleteMode(Note * note);

    /** 
     * Overrides MyWindow::printContent.
     * Prints out first page of NotesWindow::allNotes.
     */
    void printContent();

    /** 
     * Fills NotesWindow::content with NotesWindow::allNotes
     */
    void fillContent();

    /** 
     * Method to create Note from filepath.
     */
    Note * createNote(string filepath);

    /** 
     * Method to create Note from XML document.
     */
    Note * createNoteFromXml(string filepath, xmlDoc * doc, xmlNode * root_element);
    
    /** 
     * Method to parse type of Note from XML document.
     */
    string parseTypeFromXml(xmlDoc * doc, xmlNode * root_element) const;

    /** 
     * Method to parse multi-note from XML document and create and add separe notes from it.
     */
    void parseMultiNote(string filepath, xmlDoc * doc, xmlNode * root_element);

    void addNote(Note * note);
};


#endif
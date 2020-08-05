/**
 * @class SearchWindow
 * @brief Derived class from MyWindow for searching notes
 * This class implements and extends functionality of parent MyWindow. 
 * SearchWindow class introduces Window with Search functionaly.
 * User can search within imported notes by Name, Keyword, Category or Tag.
 * User can see results using paging functionality.
 * User can export searching result to file which will have few (more than one)
 * notes stored in one file. Exported file can be parse again and notes will be
 * imported into program. More about import @see NotesWindow.
 */

#ifndef SEARCH_WINDOW
#define SEARCH_WINDOW

#include "MyWindow.h"
#include "NotesWindow.h"
#include "../notes/Note.h"

#include <ncurses.h>

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <algorithm>

class SearchWindow : public MyWindow {
public:

    /** 
     * Constructor for SearchWindow.
     */
    SearchWindow(int height, int width, int startY, int startX, WINDOW * optWindow, string name, NotesWindow * notesWin);

    /** 
     * Destructor for SearchWindow.
     */
    virtual ~SearchWindow(); 
private:
    static const unsigned NAME_MODE     = 0; /**< Constant for Name mode. */
    static const unsigned KEYWORD_MODE  = 1; /**< Constant for Keyword mode. */
    static const unsigned CATEGORY_MODE = 2; /**< Constant for Category mode. */
    static const unsigned TAG_MODE      = 3; /**< Constant for Tag mode. */
    static const unsigned PREV_PAGE     = 4; /**< Constant for previous page. */
    static const unsigned NEXT_PAGE     = 5; /**< Constant for next page. */
    static const unsigned EXPORT_MODE   = 6; /**< Constant for Export mode. */

    const vector<string> searchOpt = {"Add", "Delete", "Clear"}; /**< Auxiliary options for work with search. */
    
    NotesWindow * notesWin; /**< Pointer to Notes Window for work with search. */
    vector<Note *> resultNotes; /**< Vector of pointers to Notes which is result of search. */

    string noteName; /**< Name of Note to be searched for. */
    string keyword; /**< Keyword which is looked up in every Note. */
    vector<string> categories; /**< Categories which are looked up in every Note. */
    vector<string> tags; /**< Tags which are looked up in every Note. */

    /** 
     * Implementation of MyWindow::execCurrOpt
     * Executes current chosen option.
     * By executing some Search option specific Mode (name, keyword, category or tag) is applied.
     * By executing Export option result is exported into file.
     * Also paging options are supported for listing through result of search.
     */
    virtual void execCurrOpt();

    /** 
     * Method implementing search by name.
     */
    void nameMode();

    /** 
     * Method implementing search by keyword.
     */
    void keywordMode();

    /** 
     * Method implementing search by category or tag.
     * Depending on @param mode category or tag search will be used.
     */
    void categoryOrTagMode(int mode);

    /** 
     * Method implementing export of search result.
     */
    void exportResultMode();

    /** 
     * Method to print result of search.
     * Result will be printed according to @param mode which describes Mode of search.
     */
    void printResult(int mode);
    
    /** 
     * Fills content with SearchWindow::categories.
     */
    void addCategoriesToContent();
    
    /** 
     * Fills content with SearchWindow::tags.
     */
    void addTagsToContent();

    /** 
     * Searches throughout all notes by category and fills SearchWindow::resultNotes with result.
     */
    void searchByCategory(); 
    
    /** 
     * Searches throughout all notes by tag and fills SearchWindow::resultNotes with result.
     */
    void searchByTag(); 

    /** 
     * Adds new category to SearchWindow::categories to be search for in all notes.
     * @param category is category to be added.
     */
    void addCategory(string category);

    /** 
     * Deletes category from SearchWindow::categories to be search for in all notes.
     * @param category is category to be deleted.
     */
    void deleteCategory(string category); 

    /** 
     * Adds new tag to SearchWindow::tags to be search for in all notes.
     * @param tag is tag to be added.
     */
    void addTag(string tag);

    /** 
     * Deletes tag from SearchWindow::tags to be search for in all notes.
     * @param tag is tag to be deleted.
     */
    void deleteTag(string tag); 

    /** 
     * Deletes all categories or tags from SearchWindow::categories or
     * SearchWindow::tags according to @param mode.
     */
    void clearCatOrTag(int mode);
};

#endif
/**
 * @class Content
 * @brief Represents content to be displayed in Window.
 * This class allows Window print out its content properly 
 * so text does not cross its borders. Another main feature of Content
 * is pagination i.e. if desired content does not fit size of Window, 
 * content will be splited on several pages.
 */

#ifndef CONTENT
#define CONTENT

#include <ncurses.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Content {
public:

    /** 
     * Default Constructor for Content.
     */
    Content();

    /** 
     * Constructor for Content.
     */
    Content(WINDOW * window, int height, int width);
    
    /** 
     * Destructor for Content.
     */
    ~Content() = default;

    /** 
     * @returns Content::maxWidth.
     */
    int getMaxWidth() const;

    /** 
     * @returns Content::maxWidth.
     */
    int getMaxHeight() const;
    
    /** 
     * @returns Content::currPage.
     */
    int getCurrentPageSize() const;
    
    /** 
     * @returns Number of current page.
     */
    int getCurrentPageNumber() const;
    
    /** 
     * Adds new @param line into Content::Pages.
     * Splits given @param line on several if line does not fit on Window
     * and adds to new page if needed.
     */
    void addLine(string line);

    /** 
     * Adds new line into Content::Pages, but it's presented as 2 columns
     * generated from @param left and @param right.
     */
    void addPair(string left, string right);

    /** 
     * Adds straight line to create separation within the Content.
     */
    void addStripe();

    /** 
     * Clears the Content.
     */
    void clearContent();


    /** 
     * Prints out first page of the Content with highlighted line
     * given as @param linePos. For non-highlighted content pass -1 (or any negative number).
     */
    void printFirstPage(int linePos);
    
    /** 
     * Prints out current page of the Content with highlighted line
     * given as @param linePos. For non-highlighted content pass -1 (or any negative number).
     */
    void printCurrentPage(int linePos) const;

    /** 
     * Prints out next page after current of the Content with highlighted line
     * given as @param linePos. For non-highlighted content pass -1 (or any negative number).
     */
    void printNextPage(int linePos);

    /** 
     * Prints out previous page before current of the Content with highlighted line
     * given as @param linePos. For non-highlighted content pass -1 (or any negative number).
     */
    void printPreviousPage(int linePos);

    /** 
     * Prints out error message given as @param errorMsg.
     */
    void printError(string errorMsg);

    /** 
     * Clears window.
     */
    void clear() const;

    /** 
     * Highlightes bordes of Window.
     */
    void colorBorders() const;

private:

    WINDOW * window; /**< NCurses window were Content will be printed out. */
    int maxHeight; /**< Maximum number of lines can be displayed on Window. */
    int maxWidth; /**< Maximum number of symbols can be displayed on Window. */

    int currPage; /**< Current page. */
    vector<vector<string>> pages; /**< Vector of pages (vectors of strings aka lines). */
};

#endif
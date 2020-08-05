/**
 * @class Note
 * @brief Parent class for all Notes.
 * This class has main attributes and methods for every note. 
 */

#ifndef NOTE
#define NOTE

#include "../windows/Content.h"

#include "ncurses.h"
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Note {
public:
    /**
     * Constructor for Note.
     */
    Note(string filepath);
    
    /**
     * Destructor for Note.
     */
    virtual ~Note();

    /**
     * @returns Name of Note.
     */
    string getName() const;

    /**
     * Check is word apears in Note.
     */
    virtual bool findWord(string word) const; // FIX ME

    /**
     * Fills passed @content with data from Note.
     * @param content is to be filled with data from note.
     */
    virtual void fillContent(Content * content) const;

    /**
     * Creates XML formated string out of the Note.
     * @returns object Note as string in XML format.
     */
    virtual string getXml() const;

private:
    string data; /**< Here note is stored. */

protected:
    string type; /**< Type of note. */
    string name; /**< Name of note. */
    string filePath; /**< File path to note. */

    /**
     * Creates XML formated string out of Note::data of the Note.
     * @returns Note::data in XML format.
     */
    virtual string getDataXml() const; 
};

#endif
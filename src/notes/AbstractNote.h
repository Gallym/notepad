/**
 * @class AbstractNote
 * @brief Derived class from Note for XML notes.
 * This is an abstract class which defines main behaviour of XML notes.
 * This class extends functionality of Note for more complex XML notes. 
 * Auxiliary methods are provided.
 */

#ifndef ABSTRACT_NOTE
#define ABSTRACT_NOTE

#include "Note.h"
#include "../windows/Content.h"

#include <ncurses.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <vector>
#include <string>

class AbstractNote : public Note {
public:

    /** 
     * Constructor for AbstractNote. 
     */
    AbstractNote(string filepath, xmlDoc * doc, xmlNode * root_element);
    
    /** 
     * Destructor for AbstractNote. 
     */
    ~AbstractNote();

    /** 
     * @returns Category of the Note. 
     */
    string getCategory() const;

    /**
     * @returns Tags of the Note 
     */
    vector<string> getTags() const;

    /**
     * Fills given @param content with data out of the Note to be shown later.
     */
    virtual void fillContent(Content * content) const;

    /** 
     * Checks if @param word apears in the Note. 
     * @note implementation is required in derived class.
     */
    virtual bool findWord(string word) const = 0;

    /** 
     * Implementation of Note::getXml for XML notes.
     * @returns note as string in XML format.
     */
    virtual string getXml() const; 

protected:

    string category; /**< Category of note. */
    vector<string> tags; /**< Tags of note. */

    /** 
     * Parses name, category and tags and stores them into attributes of this object.
     */
    bool parseInfo(xmlDoc * doc, xmlNode * root_element);

    /** 
     * Stores information about name, category and tags into given @param content.
     */
    virtual void addInfoToContent(Content * content) const;
    
    /** 
     * Stores data into given @param content.
     * @note implementation is required in derived class.
     */
    virtual void addDataToContent(Content * content) const = 0;

    /** 
     * Creates XML formated string out of data of the Note.
     * @note implementation of Note::getDataXml is hidden due
     * incompatability and required in derived class.
     * @returns data in XML format.
     */
    virtual string getDataXml() const = 0;
};

#endif

/**
 * @class BasicNote
 * @brief Derived class from AbstractNote.
 * BasicNote implements and extends functionality of AbstractNote. 
 * BasicNote describes Basic type of Note.
 */

#ifndef BASIC_NOTE
#define BASIC_NOTE

#include "AbstractNote.h"

#include <ncurses.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <vector>
#include <string>

class BasicNote : public AbstractNote {     
public:

    /** 
     * Constructor for BasicNote. 
     */
    BasicNote(string filepath, xmlDoc * doc, xmlNode * root_element);
    
    /** 
     * Destructor for BasicNote. 
     */
    ~BasicNote();

    /** 
     * Implementation of AbstractNote::findWord. 
     * \see AbstractNote::findWord.
     */
    virtual bool findWord(string word) const;

protected:

    /** 
     * Implementation of AbstractNote::addDataToContent. 
     * \see AbstractNote::addDataToContent.
     */
    virtual void addDataToContent(Content * content) const;
    
    /** 
     * Implementation of AbstractNote::addDataToContent. 
     * \see AbstractNote::getDataXml.
     */
    virtual string getDataXml() const;

private:

    string data; /**< Data of note. */
};

#endif
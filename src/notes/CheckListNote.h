/**
 * @class CheckListNote
 * @brief Derived class from AbstractNote for Check list XML notes.
 * This class implements and extends functionality of AbstractNote. 
 * This class describes Check list type of Note.
 */

#ifndef CHECK_LIST_NOTE
#define CHECK_LIST_NOTE

#include "BasicNote.h"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <iostream>
#include <vector>
#include <string>
#include <string.h>

class CheckListNote : public AbstractNote {
public:

    /** 
     * Constructor for BasicNote. 
     */
    CheckListNote(string filepath, xmlDoc * doc, xmlNode * root_element);

    /** 
     * Destructor for BasicNote. 
     */
    virtual ~CheckListNote() = default; 

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
    vector<pair<bool, string>> items; /**< Vector of items representing pair of check and task. */
};

#endif

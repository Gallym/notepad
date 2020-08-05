/**
 * @class PriceListNote
 * @brief Derived class from AbstractNote for Price list XML notes
 * This class implements and extends functionality of AbstractNote. 
 * This class describes Price list type of Note.
 */

#ifndef PRICE_LIST_NOTE
#define PRICE_LIST_NOTE

#include <iostream>
#include <vector>
#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "BasicNote.h"

class PriceListNote : public AbstractNote {
public:
    
    /** 
     * Constructor for BasicNote. 
     */
    PriceListNote(string filepath, xmlDoc * doc, xmlNode * root_element);
    
    /** 
     * Destructor for BasicNote. 
     */
    virtual ~PriceListNote() = default;

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
    vector<pair<string, string>> items; /**< Vector of items representing pair of article and price. */
};

#endif
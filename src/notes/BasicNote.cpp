#include "BasicNote.h"

BasicNote::BasicNote(string filepath, xmlDoc * doc, xmlNode * root_element) 
          : AbstractNote(filepath, doc, root_element) {
    type = "basic";
    xmlNode * xmlData = root_element->xmlChildrenNode->next->next->next;
    if (xmlData && !xmlStrcmp(xmlData->name, (const xmlChar *)"data")) {
        data = ((char *)(xmlNodeListGetString(doc, xmlData->xmlChildrenNode, 1)));
    } else {
        throw "Invalid XML: <data>";
    }
}

BasicNote::~BasicNote() {}

bool BasicNote::findWord(string word) const {
    size_t found = data.find(word);
    return found != string::npos;
}

void BasicNote::addDataToContent(Content * content) const {
    content->addLine(data);
}

string BasicNote::getDataXml() const {
    string dataXml;
    dataXml.append("\t<data>\n");
    dataXml.append(data + "\n");
    dataXml.append("\t</data>\n");
    return dataXml;
}
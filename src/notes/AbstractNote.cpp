#include "AbstractNote.h"

AbstractNote::AbstractNote(string filepath, xmlDoc * doc, xmlNode * root_element) 
             : Note(filepath) {
    if(!parseInfo(doc, root_element)) {
        throw "Invalid XML: <info>";
    }
}

AbstractNote::~AbstractNote() {}

string AbstractNote::getCategory() const {
    return category;
}

vector<string> AbstractNote::getTags() const {
    return tags;
}

bool AbstractNote::parseInfo(xmlDoc * doc, xmlNode * root_element) {
    bool success = true;

    xmlNode * info = root_element->xmlChildrenNode->next;
    if (info && !xmlStrcmp(info->name, (const xmlChar *)"info")) {
        xmlNode * xmlType = info->xmlChildrenNode->next;
        if (xmlType && !xmlStrcmp(xmlType->name, (const xmlChar *)"type")) {
            xmlNode * xmlName = xmlType->next->next;
            if (xmlName && !xmlStrcmp(xmlName->name, (const xmlChar *)"name")) {
                name = ((char *)(xmlNodeListGetString(doc, xmlName->xmlChildrenNode, 1)));
                xmlNode * xmlCategory = xmlName->next->next;
                if (xmlCategory && !xmlStrcmp(xmlCategory->name, (const xmlChar *)"category")) {
                    category = ((char *)(xmlNodeListGetString(doc, xmlCategory->xmlChildrenNode, 1)));
                    xmlNode * xmlTags = xmlCategory->next->next;
                    if (xmlTags && !xmlStrcmp(xmlTags->name, (const xmlChar *)"tags")) {
                        xmlNode * xmlTag = xmlTags->xmlChildrenNode->next;
                        for (; xmlTag; xmlTag = xmlTag->next) {
                            if (xmlTag->type == XML_ELEMENT_NODE ) {
                                if (xmlTag->xmlChildrenNode) {
                                    tags.push_back((char *)(xmlNodeListGetString(doc, xmlTag->xmlChildrenNode, 1)));
                                }
                            } 
                        }
                    } else {
                        success = false;
                    }
                } else {
                    success = false;
                }
            } else {
                success = false;
            }
        } else {
            success = false;
        }
    } else {
        success = false;
    }
    return success;
}

void AbstractNote::fillContent(Content * content) const {
    content->clearContent();
    addInfoToContent(content);
    addDataToContent(content);
}

void AbstractNote::addInfoToContent(Content * content) const {
    content->addLine("Name: " + name);
    content->addLine("Category: " + category);
    string tagsLine = "Tags: ";
    for (unsigned i = 0; i < tags.size(); i++) {
        tagsLine.append(tags[i]);
        if (i + 1 != tags.size()) {
            tagsLine.append(", ");
        }
    }
    content->addLine(tagsLine);
    content->addStripe();
}

string AbstractNote::getXml() const {
    string noteXml;
    noteXml.append("<note>\n");
    noteXml.append("\t<info>\n");
    noteXml.append("\t\t<type>" + type + "</type>" "\n");
    noteXml.append("\t\t<name>" + name + "</name>" "\n");
    noteXml.append("\t\t<category>" + category + "</category>" "\n");
    noteXml.append("\t\t<tags>\n");
    for(auto & tag : tags) {
        noteXml.append("\t\t\t<tag>" + tag + "</tag>\n");
    }
    noteXml.append("\t\t</tags>\n");
    noteXml.append("\t</info>\n");
    noteXml.append(getDataXml());
    noteXml.append("</note>\n");
    return noteXml;
}

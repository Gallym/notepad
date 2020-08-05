#include "CheckListNote.h"

CheckListNote::CheckListNote(string filepath, xmlDoc * doc, xmlNode * root_element) 
              : AbstractNote(filepath, doc, root_element), 
              items() {
    type = "checklist";
    bool success = true;
    
    xmlNode * data = root_element->xmlChildrenNode->next->next->next;
    if (data && !xmlStrcmp(data->name, (const xmlChar *)"data")) {
        string line;
        xmlNode * item = data->xmlChildrenNode->next;
        for (; item; item = item->next) {
            if (item->type == XML_ELEMENT_NODE ) {
                if (item->xmlChildrenNode && item->xmlChildrenNode->next) {
                    xmlNode * xmlCheck = item->xmlChildrenNode->next;
                    bool isChecked = false;
                    if (strcmp("true", (char *)(xmlNodeListGetString(doc, xmlCheck->xmlChildrenNode, 1))) == 0) {
                        isChecked = true;
                    } 

                    xmlNode * xmlTask = xmlCheck->next;
                    string task; 
                    if (!xmlStrcmp(xmlTask->name, (const xmlChar *)"task")) {
                        task = (char *)(xmlNodeListGetString(doc, xmlTask->xmlChildrenNode, 1));
                        items.push_back(make_pair(isChecked, task));
                    } else {
                        success = false;
                        break;
                    }
                } else {
                    success = false;
                    break;
                }
            }
        }
    }

    if (!success) throw "throw Invalid XML: <data>";
}

void CheckListNote::addDataToContent(Content * content) const {
    for (const auto & item : items) {
        content->addLine("["s + (item.first ? "x" : " ") + "] " + item.second);
    }
}

bool CheckListNote::findWord(string word) const {
    for (unsigned i = 0; i < items.size(); i++) {
        if (items[i].second.find(word) != string::npos) {
            return true;
        }
    }
    return false;
}
string CheckListNote::getDataXml() const {
    string dataXml;
    dataXml.append("\t<data>\n");
    for (auto & item : items) {
        dataXml.append("\t\t<item>\n");
        dataXml.append("\t\t\t<check>" + (item.first ? "true"s : "false"s) + "</check>");
        dataXml.append("<task>" + item.second + "</task>\n");
        dataXml.append("\t\t</item>\n");
    }
    dataXml.append("\t</data>\n");
    return dataXml;
}
#include "PriceListNote.h"

PriceListNote::PriceListNote(string filepath, xmlDoc * doc, xmlNode * root_element) 
              : AbstractNote(filepath, doc, root_element),
              items() {
    type = "pricelist";
    bool success = true;

    xmlNode * data = root_element->xmlChildrenNode->next->next->next;
    if (data && !xmlStrcmp(data->name, (const xmlChar *)"data")) {
        string article;
        string price;
        xmlNode * item = data->xmlChildrenNode->next;
        for (; item; item = item->next) {
            if (item->type == XML_ELEMENT_NODE ) {
                if (item->xmlChildrenNode && item->xmlChildrenNode->next 
                    && !xmlStrcmp(item->xmlChildrenNode->next->next->name, (const xmlChar *)"price")) {
                    article = string((char *)(xmlNodeListGetString(doc, item->xmlChildrenNode->next->xmlChildrenNode, 1)));
                    price   = (char *)(xmlNodeListGetString(doc, item->xmlChildrenNode->next->next->xmlChildrenNode, 1));
                    items.emplace_back(make_pair(article, price));
                } else {
                    success = false;
                    break;
                }
            }
        }
    } else {
        success = false;
    }
    if (!success) throw "throw Invalid XML: <data>";
}

void PriceListNote::addDataToContent(Content * content) const {
    int total = 0;
    content->addPair("Article", "Price");
    for (const auto & item : items) {
        total += stoi(item.second);
        content->addPair(item.first, item.second);
    }
    content->addStripe();
    content->addLine("Total: "s + to_string(total));
}

string PriceListNote::getDataXml() const {
    string dataXml;
    dataXml.append("\t<data>\n");
    for (auto & item : items) {
        dataXml.append("\t\t<item>\n");
        dataXml.append("\t\t\t<article>" + item.first + "</article>");
        dataXml.append("<price>" + item.second + "</price>\n");
        dataXml.append("\t\t</item>\n");
    }
    dataXml.append("\t</data>\n");

    return dataXml;
}

bool PriceListNote::findWord(string word) const {
    for (unsigned i = 0; i < items.size(); i++) {
        size_t found = items[i].second.find(word);
        if (found != string::npos) {
            return true;
        }
    }
    return false;
}
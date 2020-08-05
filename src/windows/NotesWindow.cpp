#include "NotesWindow.h"

NotesWindow::NotesWindow(int height, int width, int startY, int startX, WINDOW * optWindow, PreviewWindow * prevWin, string name):
        MyWindow(height, width, startY, startX, optWindow, name, {"Select", "Import", "Delete"}), 
        prevWindow(prevWin) {}

NotesWindow::~NotesWindow() {
    for (unsigned i = 0; i < allNotes.size(); i++) {
        delete allNotes[i];
    }
}

void NotesWindow::execCurrOpt() {
    Note * note;
    switch (currOpt) {
    case SELECT_MODE: 
        note = selectMode();
        if (note != nullptr) prevWindow->setAndPrintPreviewNote(note);
        break;
    case IMPORT_MODE: 
        note = importMode();
        if (note != nullptr) { 
            prevWindow->setAndPrintPreviewNote(note);
            fillContent();
        }
        content.printFirstPage(-1);
        break;
    case DELETE_MODE: 
        note = selectMode();
        if (note != nullptr) deleteMode(note);
        content.printFirstPage(-1);
        break;
    default:
        break;
    }
}

void NotesWindow::fillContent() {
    content.clearContent();
    for (unsigned i = 0; i < allNotes.size(); i++) {
        content.addLine(allNotes[i]->getName());
    }
}

void NotesWindow::printContent() {
    content.clearContent();
    fillContent();
    content.printFirstPage(-1);
    colorBorders();
}

Note * NotesWindow::selectMode() {
    updateTitle("Choose Note");
    keypad(window, true);
    int currentLine = 0;
    int currKey = 0;
    if (allNotes.empty()) {
        content.printError("No available notes.");
        return nullptr;
    }

    fillContent();
    content.printFirstPage(currentLine);
    while(1) {
        currKey = wgetch(window);
        switch (currKey) {
            case KEY_UP:
                if (--currentLine < 0) currentLine = 0;
                content.printCurrentPage(currentLine);
                break;
            case KEY_DOWN:
                if (++currentLine >= content.getCurrentPageSize() - 1) {  
                    currentLine = content.getCurrentPageSize() - 1;
                }
                content.printCurrentPage(currentLine);
                break;
            case KEY_LEFT:
                currentLine = 0;
                content.printPreviousPage(currentLine);
                break;
            case KEY_RIGHT: 
                currentLine = 0;
                content.printNextPage(currentLine);
                break;
            case PREVIEW:
                if (content.getCurrentPageNumber() * content.getMaxHeight() + currentLine < (int)allNotes.size())
                    prevWindow->setAndPrintPreviewNote(allNotes[content.getCurrentPageNumber() * content.getMaxHeight() + currentLine]);
                break;
            case ENTER:
                if (content.getCurrentPageNumber() * content.getMaxHeight() + currentLine < (int)allNotes.size())
                    return allNotes[content.getCurrentPageNumber() * content.getMaxHeight() + currentLine];
                else
                    return nullptr;
            default:
                break;
        }
    }
}

Note * NotesWindow::importMode() {
    clearOptions();
    updateTitle("Import Note");

    string filepath = readInput();
    if (filepath.empty()) return nullptr;
    Note * note = nullptr;
    
    input.open(filepath);
    if (!input) {
        clear();
        content.printError("Filepath is incorrect or file does not exist!:");
        input.close();
        return note;
    }
    
    return createNote(filepath);
}

void NotesWindow::deleteMode(Note * note) {
    updateTitle("Delete Note");
    for (unsigned i = 0; i < allNotes.size(); i++) {
        if (allNotes[i] == note) {
            if (prevWindow->getPreviewNote() == note) {
                prevWindow->setAndPrintPreviewNote(nullptr);
            }
            delete note;
            allNotes.erase(allNotes.begin() + i);
            fillContent();
            return;
        }
    }
}

Note * NotesWindow::createNote(string filepath) {
    Note * note = nullptr;
    if (filepath.substr(filepath.size()-4) ==  ".xml"s/* == &filepath.back()-3*/) { // TODO check if less than 4
        // open XML parser
        xmlDoc * doc = xmlReadFile(filepath.c_str(), NULL, 0);
        if (doc == NULL) {
            content.printError("File has invalid structure: " + filepath);
            xmlCleanupParser();
            return nullptr;
        }
        
        xmlNode * root_element = xmlDocGetRootElement(doc);
        try {
            note = createNoteFromXml(filepath, doc, root_element);
        } catch (const char * exc) {
            content.printError(exc);
        }
        // clean after XML parser
        xmlFreeDoc(doc);
        xmlCleanupParser();
    } else if (filepath.substr(filepath.size()-4) == ".txt") {
        try {
            note = new Note(filepath);
            //allNotes.push_back(note);
            addNote(note);
        } catch (const char * exc) {
            content.printError(exc);
        }
    } else {
        content.printError("Error: can read only XML or TXT");
        return nullptr;
    }

    return note;
}

Note * NotesWindow::createNoteFromXml(string filepath, xmlDoc * doc, xmlNode * root_element) {
    Note * note = nullptr;
    string type = parseTypeFromXml(doc, root_element);

    if (type.empty()) return nullptr; // invalid structure of document

    if (type == "basic") {
        note = new BasicNote(filepath, doc, root_element);
    } else if (type == "checklist") {
        note = new CheckListNote(filepath, doc, root_element);
    } else if (type == "pricelist") {
        note = new PriceListNote(filepath, doc, root_element);
    } else if (type == "multinote") {
        parseMultiNote(filepath, doc, root_element);
        return nullptr;
    }
    //allNotes.push_back(note);
    addNote(note);
    return note;
}

string NotesWindow::parseTypeFromXml(xmlDoc * doc, xmlNode * root_element) const {
    if (root_element && !xmlStrcmp(root_element->name, (const xmlChar *)"multinote")) {  
        return "multinote";
    }

    xmlNode * info = root_element->xmlChildrenNode->next;
    if (info && !xmlStrcmp(info->name, (const xmlChar *)"info")) {
        xmlNode * xmlType = info->xmlChildrenNode->next;
        if (xmlType && !xmlStrcmp(xmlType->name, (const xmlChar *)"type")) {
            return (char *)(xmlNodeListGetString(doc, xmlType->xmlChildrenNode, 1));
        }
    }
    return "";
}

void NotesWindow::parseMultiNote(string filepath, xmlDoc * doc, xmlNode * root_element) {
    xmlNode * xmlNote = root_element->xmlChildrenNode->next;
    for (; xmlNote; xmlNote = xmlNote->next) {
        if (xmlNote->type == XML_ELEMENT_NODE ) {
            createNoteFromXml(filepath, doc, xmlNote);
        }
    }
}

vector<Note *> NotesWindow::getNotes() const {
    return allNotes;
}

void NotesWindow::addNote(Note * note) {
    if (note == nullptr) return;

    for (auto n : allNotes) {
        if (n->getName() == note->getName()) return;
    }

    allNotes.push_back(note);
}
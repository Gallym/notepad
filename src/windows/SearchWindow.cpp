#include "SearchWindow.h"

SearchWindow::SearchWindow(int height, int width, int startY, int startX, WINDOW * optWindow, string name, NotesWindow * notesWin):
        MyWindow(height, width, startY, startX, optWindow, name, {"By Name","By Keyword", "By Category", "By Tag", "Prev page", "Next page", "Export result"}), 
        notesWin(notesWin) {}

SearchWindow::~SearchWindow() {
    resultNotes.clear();
} 

void SearchWindow::execCurrOpt() {
    switch (currOpt) {
    case NAME_MODE: 
        nameMode();
        break;
    case KEYWORD_MODE: 
        keywordMode();
        break;
    case CATEGORY_MODE: 
        categoryOrTagMode(2);
        break;
    case TAG_MODE: 
        categoryOrTagMode(3);
        break;
    case PREV_PAGE:
        content.printPreviousPage(-1);
        break;
    case NEXT_PAGE:
        content.printNextPage(-1);
        break;
    case EXPORT_MODE: 
        exportResultMode();
        break;
    default:
        break;
    }
}

void SearchWindow::nameMode() {
    clearOptions();
    clear();
    resultNotes.clear();

    updateTitle("By Name");
    mvwprintw(window, 1, 1, "Type name and press ENTER");
    wrefresh(window);
    noteName = readInput();
    for (auto note : notesWin->getNotes()) {
        AbstractNote * bnote = dynamic_cast<AbstractNote *>(note);
        if (bnote && noteName == bnote->getName()) resultNotes.push_back(note);
    }
    printResult(NAME_MODE);
}

void SearchWindow::keywordMode() {
    clearOptions();
    clear();
    resultNotes.clear();

    updateTitle("By Keyword");
    mvwprintw(window, 1, 1, "Type keyword and press ENTER");
    wrefresh(window);

    keyword = readInput();
    mvwprintw(window, 1, 1, keyword.c_str());
    wrefresh(window);
    for (auto note : notesWin->getNotes()) {
        if (note->findWord(keyword)) resultNotes.push_back(note);
        //updateTitle(to_string())
    }
    printResult(KEYWORD_MODE);
}

void SearchWindow::categoryOrTagMode(int mode) {
    clear();
    resultNotes.clear();

    updateTitle(string("By ") + (mode==2 ? "Category" : "Tag"));
    mvwprintw(window, 1, 1, (string("Add ") + (mode == 2 ? "category" : "tag") + " and press ENTER").c_str());
    wrefresh(window);
    int currKey;
    currOpt = 0;
    while(1) {
        keypad(optWindow, true);
        printThisOptions(searchOpt);
        
        currKey = wgetch(optWindow);
        refresh();
        switch (currKey) {
            case KEY_LEFT:
                if (--currOpt < 0) currOpt = 0;
                break;
            case KEY_RIGHT:
                if (++currOpt >= (int)searchOpt.size()) {  currOpt = searchOpt.size() - 1; }
                break;
            case 10: // ENTER KEY
                switch (currOpt) {
                case 0: { // Add
                    clearOptions();
                    string item = readInput();
                    if (mode == CATEGORY_MODE) {
                        addCategory(item);
                        searchByCategory();
                    } else {
                        addTag(item);
                        searchByTag();
                    }           
                    printResult(mode);
                    break;
                } case 1: { // Delete
                    string item = readInput();
                    if (mode == CATEGORY_MODE) {
                        deleteCategory(item); 
                        searchByCategory();
                    } else {
                        deleteTag(item);
                        searchByTag();
                    }
                    printResult(mode);
                    break;
                } case 2: { // Clear
                    clearCatOrTag(mode);
                    break;
                } default: { break; }
                }
                currOpt = 0;
                break;
            case QUIT: 
                clear();
                currOpt = (mode == CATEGORY_MODE ? CATEGORY_MODE : TAG_MODE);
                return;
            default:
                break;
        }
        
        wrefresh(optWindow);
        refresh();
    }
}

void SearchWindow::exportResultMode() {
    if (resultNotes.size() <= 2) {
        content.printError("2 and more notes needed to export!");
        return;
    }

    ofstream MyFile("my_multinote.xml");
    
    MyFile<<"<multinote>\n";
    for (auto & note : resultNotes) {
        MyFile << note->getXml();
    }
    MyFile<<"</multinote>\n";

    MyFile.close();
}

void SearchWindow::printResult(int mode) { 
    clear();
    content.clearContent();

    string subTitle = "Searched by ";
    switch (mode) {
    case NAME_MODE:
        subTitle.append("Name:");
        content.addLine(subTitle);
        content.addLine(noteName);
        break;
    case KEYWORD_MODE:
        subTitle.append("Keyword:");
        content.addLine(subTitle);
        content.addLine(keyword);
        break;
    case CATEGORY_MODE:
        subTitle.append("Category:");
        content.addLine(subTitle);
        addCategoriesToContent();
        break;
    case TAG_MODE:
        subTitle.append("Tag:");
        content.addLine(subTitle);
        addTagsToContent();
        break;
    default:
        break;
    }
    content.addStripe();
    if (resultNotes.empty()) {
        content.addLine("No notes were found :(");
    } else {
        for (unsigned i = 0; i < resultNotes.size(); i++) {
            content.addLine(resultNotes[i]->getName());
        }
    }
    content.printFirstPage(-1);
    wrefresh(window);
}

void SearchWindow::addCategoriesToContent() {
    clear();
    if (categories.empty()) {
        return;
    }

    for (auto & category : categories) {
        content.addLine(category);
    }
}

void SearchWindow::addTagsToContent() {
    clear();
    if (tags.empty()) {
        content.addLine("Add tag for Search");
        return;
    }

    for(auto & tag : tags) {
        content.addLine(tag);
    }
}

void SearchWindow::searchByCategory() { // Search all notes with at least one mentioned category
    resultNotes.clear();
    for (auto note : notesWin->getNotes()) {
        AbstractNote * bnote = dynamic_cast<AbstractNote *>(note);
        if (bnote) {
            for (const auto & cat : categories) {
                if (cat == bnote->getCategory()) {
                    resultNotes.push_back(note);
                    break;
                }
            } 
            
        } 
    }
}
void SearchWindow::searchByTag() { // Search all notes with all mentioned tags
    resultNotes.clear();
    vector<string> tagsTmp = tags;
    sort(tagsTmp.begin(), tagsTmp.end());
    for (auto note : notesWin->getNotes()) {
        AbstractNote * bnote = dynamic_cast<AbstractNote *>(note);
        if (bnote) {
            vector<string> noteTagsTmp = bnote->getTags();
            sort(noteTagsTmp.begin(), noteTagsTmp.end());
            if (noteTagsTmp == tagsTmp)
                resultNotes.push_back(note);
        } 
    }
}

void SearchWindow::addCategory(string category) {
    for (const auto & cat : categories) {
        if (cat == category) return; 
    }
    categories.push_back(category);
}

void SearchWindow::deleteCategory(string category) {
    for (unsigned i = 0; i < categories.size(); i++) {
        if (category == categories[i]) 
            categories.erase(categories.begin() + i - 1); 
    }
}

void SearchWindow::addTag(string tag) {
    for (const auto & t : tags) {
        if (t == tag) return; 
    }
    tags.push_back(tag);
}

void SearchWindow::deleteTag(string tag) {
    for (unsigned i = 0; i < tags.size(); i++) {
        if (tag == tags[i]) 
            tags.erase(tags.begin() + i - 1); 
    }
}

void SearchWindow::clearCatOrTag(int mode) {
    clear();
    if (mode == CATEGORY_MODE) { 
        categories.clear();
        mvwprintw(window, 1, 1, "Add category for Search");
    } else {     
        tags.clear();
        mvwprintw(window, 1, 1, "Add tag for Search");
    }
    wrefresh(window);
    resultNotes.clear();
}
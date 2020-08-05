#include "Note.h"

Note::Note(string filepath) : data(""), 
                        type ("note"), 
                        name(filepath), 
                        filePath(filepath) {
        fstream input;
        input.open(filePath, ios::in);
        if (!input) {
            input.close();
            throw "Could note open file.";
        }

        string line;
        while(getline(input, line)) {
            data.append(line);
        }
        input.close();
}

Note::~Note() {}

string Note::getName() const {
    return name;
}

bool Note::findWord(string word) const {
    // input.open(filePath);
    // while (true) {
    //     char line[1024];
    //     //char * newLine;
    //     input.getline(line, 1024);
    //     //input.readsome(line, 1024);
    //     mvwprintw(window, tmpY, tmpX, line);
    //     tmpY++;
    //     if( input.eof() ) break;
    // }
    // input.close();
    
    istringstream iss(data);
    string line;
    while (getline(iss, line)) {
        if (line.find(word) != string::npos) {
            return true;
        }
    }

    return false;
}

void Note::fillContent(Content * content) const {
    content->addLine(data);
}

string Note::getXml() const {
    string noteXml;
    noteXml.append("<note>\n")
           .append(getDataXml())
           .append("</note>\n");
    return noteXml;
}

string Note::getDataXml() const {
    string dataXml;
    dataXml.append("\t<data>\n");
    dataXml.append(data + "\n");
    dataXml.append("\t</data>\n");
    return dataXml;
}
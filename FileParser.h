//
// Created by eden on 26/12/2019.
//

#ifndef EX3_FILEPARSER_H
#define EX3_FILEPARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "ConnectCommand.h"
#include "Command.h"

using namespace std;

class FileParser {
public:
    FileParser();
    ~FileParser();

    vector<string> lexer(char *file_name);
    void parser (vector<string> arrayVector);

private:
    typedef unordered_map<string, Command*>  CommandMapType;
    CommandMapType cmdMap;
};


#endif //EX3_FILEPARSER_H

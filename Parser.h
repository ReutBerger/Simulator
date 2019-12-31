//
// Created by eden on 26/12/2019.
//

#ifndef EX3_PARSER_H
#define EX3_PARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "ConnectCommand.h"
#include "Command.h"

using namespace std;

class Parser {
public:
    Parser();
    ~Parser();

    vector<string> lexer(char *file_name);
    bool is_operator(char c);
    void parser (vector<string> arrayVector);

private:
    typedef unordered_map<string, Command*>  CommandMapType;
    CommandMapType cmdMap;
};


#endif //EX3_PARSER_H

//
// Created by eden on 26/12/2019.
//

#include "Parser.h"

#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "ConditionParser.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "SetVal.h"


Parser::Parser() {
    auto *osc = new OpenServerCommand();
    auto *cc  = new ConnectCommand();
    auto *dvc = new DefineVarCommand();
    auto *sv  = new SetVal(cc);
    auto *pc = new PrintCommand();
    auto *sc = new SleepCommand();
    auto *cp = new ConditionParser();

    cmdMap.insert(make_pair("openDataServer",       osc));
    cmdMap.insert(make_pair("connectControlClient", cc));
    cmdMap.insert(make_pair("var",                  dvc));
    cmdMap.insert(make_pair("=",                    sv));
    cmdMap.insert(make_pair("Print",                pc));
    cmdMap.insert(make_pair("Sleep",                sc));
    cmdMap.insert(make_pair("if",                   cp));
    cmdMap.insert(make_pair("while",                cp));
}

Parser::~Parser() {
    // Release memory allocations for all command objects
    CommandMapType::iterator it = cmdMap.begin();
    while (it != cmdMap.end()) {
        delete(it->second);
        it++;
    }
}

vector<string> Parser::lexer(char *file_name) {
    ifstream in_file;
    in_file.open(file_name);
    if (!in_file)
        throw ("File open error");

    // treatment for each line
    vector<string> vec;
    string line{};
    string token;
    while (!in_file.eof()) {
        getline(in_file, line);
if (line[0] == '#') continue;
        size_t i = 0;
        bool inExpression = false;
        while (i <= line.length()) {
            //TODO : try with exp //
            token = "";
            if ((!vec.empty()) && ((vec.back() == "openDataServer") || (vec.back() == "Print") || (vec.back() == "Sleep")))
            {
                token = line.substr(0, line.length() - 1);
                line.clear();
                if (token != "") {
                    vec.push_back(token);
                }
                break;
            }
            if ((vec.size() >= 2 ) && (vec[vec.size() - 2] == "connectControlClient"))
            {
                token = line.substr(0, line.length() - 1);
                line.clear();
                if (token != "") {
                    vec.push_back(token);
                }
                // maybe continue??
                break;
            }
            if ((!vec.empty()) && (vec.back() == "while" || vec.back() == "if")) {
                /* delete -> */  inExpression = true;
                token = line;
                string left = "";
                string sign = "";
                string right = "";
                int index = 0;
                while (!is_operator(token[index])) {
                    left += token[index];
                    index++;
                }
                if (token != "") {
                    vec.push_back(left);
                }
                sign += token[index];
                index++;
                if (token[index] == '=')
                {
                    sign += token[index];
                }
                if (token != "") {
                    vec.push_back(sign);
                }
                index++;
                while (token[index] != '{') {
                    right += token[index];
                    index++;
                }
                if (token != "") {
                    vec.push_back(right);
                }
                string last = "";
                last += token[index];
                vec.push_back(last);
                break;
            }
            if (line[i] == '(' || line[i] == ')' || (line[i] == ' ' && line[0]!= '"') ||
                line[i]== ',' || line[i] == '\0') {
                token = line.substr(0, i);
                if (line[i] == ' ') {
                    while (line[i + 1] == ' ') {
                        i++;
                    }
                }
                line.erase(0, i + 1);
                i = 0;
                if (token != "") {
                    vec.push_back(token);
                }
            }
            if(line[i] == '=' /* maybe delete it -> */ && !inExpression) {
                token = line.substr(0, i);
                while (line[i + 1] == ' ') {
                    i++;
                }
                line.erase(0, i + 1);
                i = 0;
                if (token != "") {
                    vec.push_back(token);
                }
                vec.push_back("=");
                token = line.substr(0, line.length());
                line.clear();
                i = 0;
                vec.push_back(token);
            }
            if (line[i] == '\t'){
                line.erase(0,i + 1);
                i = 0;
                // maybe not necessary
            } if (line[i] == '{') {
                inExpression = false;
            }
            i++;
        }
    }
    in_file.close();
    return  vec;
}

bool Parser:: is_operator(char c) {
    if (c == '<' || c == '>' || c == '!' || c == '=')
    {
        return true;
    }
    return false;
}

void Parser::parser (vector<string> arrayVector) {
    uint32_t index = 0;
    Command *c;

    while (index < arrayVector.size()) {
        CommandMapType::const_iterator it = cmdMap.find (arrayVector[index]);

        // If command was not found in the map, move to the next index in the vector
        if (it == cmdMap.end()) {
            index++;
            if (!arrayVector[index + 1].compare("="))
                cout << "command not found" << endl;
            continue;
        }

        // Execute command and set the index to next command string
        c = it->second;
        index += c->execute(arrayVector, ++index);
    }
}

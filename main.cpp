#include <iostream>
#include <vector>
#include <unordered_map>
#include <unistd.h>
#include <fstream>

#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "ConditionParser.h"
#include "PrintCommand.h"
#include "SleepCommand.h"

using namespace std;

typedef unordered_map<string, Command*>  CommandMapType;
CommandMapType cmdMap;

int parser (vector<string> arrayVector) {
    int index = 0;
    Command *c;

    while (index < arrayVector.size()) {
        CommandMapType::const_iterator it = cmdMap.find (arrayVector[index]);

        // If command was not found in the map, move to the next index in the vector
        if (it == cmdMap.end()) {
            index++;
            cout << "command not found" << endl;
            continue;
        }

        // Execute command and set the index to next command string
        c = it->second;
        index += c->execute(arrayVector, ++index);
    }

    return 0;
}

vector<string> lexer(char *file_name) {
    ifstream in_file;
    in_file.open(file_name);
    if (!in_file){
        throw ("File open error");
    }
    // treatment for each line
    vector<string> vec;
    string line{};
    string token;
    while (!in_file.eof()) {
        getline(in_file, line);
        size_t i = 0;
        bool inExpression = false;
        while (i <= line.length()) {
            if (line[i] == '(' || line[i] == ')' || (line[i] == ' ' && line[0]!= '"') ||
                line[i]== ',' || line[i] == '\0') {
                token = line.substr(0, i);
                if(line[i] == ' ') {
                    while (line[i + 1] == ' ') {
                        i++;
                    }
                }
                line.erase(0, i + 1);
                i = 0;
                if (token != ""){
                    vec.push_back(token);
                }
            }
            if (!(vec.empty()) && (vec.back() == "while" || vec.back() == "if")) {
                inExpression = true;
            }
            if(line[i] == '=' && !inExpression) {
                token = line.substr(0, i);
                while (line[i+1] == ' ') {
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
            } if (line[i] == '{') {
                inExpression = false;
            }
            i++;
        }
    }
    in_file.close();
    return  vec;
}

int main(int argc, char *argv[]) {
    // Create the string/command mapping
    cmdMap.insert(make_pair("openDataServer",       new OpenServerCommand));
    cmdMap.insert(make_pair("connectControlClient", new ConnectCommand));
    cmdMap.insert(make_pair("var",                  new DefineVarCommand));
    cmdMap.insert(make_pair("Print",                new PrintCommand));
    cmdMap.insert(make_pair("Sleep",                new SleepCommand));
    cmdMap.insert(make_pair("if",                   new ConditionParser));
    cmdMap.insert(make_pair("while",                new ConditionParser));

    // read file and initialize the vector
    vector<string> arrayVector = lexer(argv[1]);

    // Execute all commands from the vector
    parser(arrayVector);

sleep(3600);

    return 0;
}
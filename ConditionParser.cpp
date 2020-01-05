//
// Created by eden on 22/12/2019.
//

#include "ConditionParser.h"
#include "Interpreter.h"
#include "Parser.h"

extern Parser fileParser;

bool ConditionParser::condition_is_true() {
    double val1 = Calculate(exp1);
    double val2 = Calculate(exp2);

    if (this->sign == "<=" && val1 <= val2)
    {
        return true;
    }
    if (this->sign == ">=" && val1 >= val2)
    {
        return true;
    }
    if (this->sign == "==" && val1 == val2)
    {
        return true;
    }
    if (this->sign == "!=" && val1 != val2)
    {
        return true;
    }
    if (this->sign == ">" && val1 > val2)
    {
        return true;
    }
    if (this->sign == "<" && val1 < val2)
    {
        return true;
    }
    return false;
}

int ConditionParser:: execute(vector<string> arr, int index) {
    // Update provided values
    this->exp1 = arr[index];
    this->sign = arr [index + 1];
    this->exp2 = arr[index + 2];
    vector<string> new_commands;
    int count_commands = 0;
    // Create a new list of commands that exist only within the condition
    while (arr[index + 4 + count_commands] != "}") {
        new_commands.push_back(arr[index + 4 + count_commands]);
        count_commands++;
    }
    // Check which command it is,
    // and execute the command list until the condition no longer exists
    if (arr[index - 1] == "while")
    {
        while(condition_is_true()) {
            fileParser.parser(new_commands);
        }
    } else {
        // arr[index - 1] == "if"
        if (condition_is_true()) {
            fileParser.parser(new_commands);
        }
    }
    // We handled (5 + num of commands) parameters
    return 5 + count_commands - 1;
}

ConditionParser:: ~ConditionParser(){
}
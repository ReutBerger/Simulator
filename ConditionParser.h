//
// Created by eden on 22/12/2019.
//

#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H

#include <iostream>
#include <vector>

#include "Command.h"
#include "Expression.h"

using namespace std;

class ConditionParser : public Command
{
private:
    string exp1;
    string exp2;
    string sign;
public:
    ConditionParser() {};
    bool condition_is_true();
    virtual int execute(vector<string> arr, int index);
    ~ConditionParser();
};

#endif //EX3_CONDITIONPARSER_H
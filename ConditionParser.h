//
// Created by eden on 22/12/2019.
//

#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H

#include "Command.h"


class ConditionParser : public Command {
public:
    int execute(vector<string> arr, int index);

};


#endif //EX3_CONDITIONPARSER_H
//
// Created by eden on 22/12/2019.
//

#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H

#include "Command.h"


class PrintCommand : public Command {
public:
    int execute(vector<string> arr, int index);

};


#endif //EX3_PRINTCOMMAND_H

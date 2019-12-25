//
// Created by eden on 22/12/2019.
//

#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H

#include "Command.h"


class SleepCommand : public Command {
public:
    int execute(vector<string> arr, int index);

};


#endif //EX3_SLEEPCOMMAND_H

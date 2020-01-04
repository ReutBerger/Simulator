//
// Created by eden on 19/12/2019.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H

#include "Command.h"

class DefineVarCommand : public Command {
public:
    DefineVarCommand() {};
//    virtual ~DefineVarCommand();

    int execute(vector<string> arr, int index);
};

extern DefineVarCommand cmdDefineVar;

#endif //EX3_DEFINEVARCOMMAND_H
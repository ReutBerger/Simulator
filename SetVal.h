//
// Created by eden on 28/12/2019.
//

#ifndef EX3_SETVAL_H
#define EX3_SETVAL_H

#include "ConnectCommand.h"
#include "Command.h"

class SetVal : public Command {
public:
    SetVal(ConnectCommand *cc) {mCC = cc;}
//    virtual ~SetVal();

    int execute(vector<string> arr, int index);

private:
    ConnectCommand *mCC;
};


#endif //EX3_SETVAL_H
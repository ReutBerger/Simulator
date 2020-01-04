//
// Created by eden on 19/12/2019.
//

#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H

#include <iostream>
#include <semaphore.h>
#include <vector>

#include "Command.h"


class OpenServerCommand: public Command {
public:
    OpenServerCommand();
    ~OpenServerCommand() {};

    int execute(vector<string> arr, int index);
    int openServerFunc();

private:
    vector<string> mNodes;
    int mPort;
    sem_t mSync;
};

extern OpenServerCommand cmdOpenServer;


#endif //EX3_OPENSERVERCOMMAND_H
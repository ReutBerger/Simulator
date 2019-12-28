//
// Created by eden on 19/12/2019.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H

#include <iostream>
#include <semaphore.h>

#include "Command.h"

class ConnectCommand : public Command {
public:
    ConnectCommand() {};
    ~ConnectCommand() {};

    int execute(vector<string> arr, int index);
    int connectClientFunc();
    void sendData(string buffer);

private:
    uint32_t mAddr;
    int      mPort;

    int      msqid;

    sem_t    mSync;
};

extern ConnectCommand cmdConnect;

#endif //EX3_CONNECTCOMMAND_H
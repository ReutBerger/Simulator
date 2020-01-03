//
// Created by eden on 19/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <vector>
using namespace std;

/**
 * Command Interface
 */

#include <iostream>

class Command {
public:
    Command() {};
    virtual ~Command() {};

    virtual int execute(vector<string> /*arr*/, int /*index*/) {
        return 0;
    }
};

#endif //EX3_COMMAND_H
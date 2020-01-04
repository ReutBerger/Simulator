//
// Created by eden on 19/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <vector>
#include <iostream>

#include "Interpreter.h"

using namespace std;

/**
 * Command Interface
 */
class Command {
public:
    Command() {};
    virtual ~Command() {};

    virtual int execute(vector<string> /*arr*/, int /*index*/) {
        return 0;
    }

    virtual double Calculate(string &buf) {
        Expression *exp = nullptr;
        double val = 0;

        try {
            exp = i1.interpret(buf.c_str());
            val = exp->calculate();
        } catch(const char *e) {
            std::cout << e << std::endl;
        }

        if (exp != nullptr)
            delete exp;
        return val;
    }

private:
    Interpreter i1;
};

#endif //EX3_COMMAND_H
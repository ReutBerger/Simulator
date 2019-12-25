//
// Created by eden on 25/12/2019.
//

#ifndef EX3_VARIABLE_H
#define EX3_VARIABLE_H


#include "Expression.h"
#include <iostream>

using namespace std;

typedef enum {
    DIR_IN = 0,
    DIR_OUT
} VarDirE;

class Variable: public Expression {
    string  mName;
    string  mSim;
    VarDirE mDirection;
    float   mValue;

public:
    // Constructor
    Variable (string name, string sim, VarDirE dir)
        : mName(name), mSim(sim), mDirection(dir), mValue(0)
    {}

    ~Variable() {}

    string getName();

    VarDirE getDirection();

    float getVal();
    void  setVal(float val);

    Variable& operator++();
    Variable& operator++(int);

    Variable& operator--();
    Variable&  operator--(int);

    Variable& operator+=(double num);
    Variable& operator-=(double num);

    double calculate() override;
};



#endif //EX3_VARIABLE_H

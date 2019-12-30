//
// Created by eden on 11/11/2019.
//

#ifndef EX1_MUL_H
#define EX1_MUL_H

#include "BinaryOperator.h"
#include <iostream>
using namespace std;

class Mul: public BinaryOperator {

public:
    Mul (Expression* left, Expression* right);

    double calculate();

    virtual ~Mul();
};


#endif //EX1_MUL_H

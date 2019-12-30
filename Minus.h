//
// Created by eden on 11/11/2019.
//

#ifndef EX1_MINUS_H
#define EX1_MINUS_H


#include "BinaryOperator.h"
#include <iostream>
using namespace std;

class Minus: public BinaryOperator {

public:
    Minus (Expression* left, Expression* right);

    double calculate();

    virtual ~Minus();
};


#endif //EX1_MINUS_H

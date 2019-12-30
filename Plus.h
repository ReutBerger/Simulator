//
// Created by eden on 11/11/2019.
//

#ifndef EX1_PLUS_H
#define EX1_PLUS_H

#include "BinaryOperator.h"
#include <iostream>
using namespace std;

class Plus: public BinaryOperator {

public:
    Plus(Expression* left, Expression* right);

    double calculate();

    virtual ~Plus();
};


#endif //EX1_PLUS_H
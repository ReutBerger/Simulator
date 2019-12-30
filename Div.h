//
// Created by eden on 11/11/2019.
//

#ifndef EX1_DIV_H
#define EX1_DIV_H

#include "BinaryOperator.h"
#include <iostream>
using namespace std;

class Div: public BinaryOperator {

public:
    Div (Expression* left, Expression* right);

    double calculate();

    virtual ~Div();
};


#endif //EX1_DIV_H

//
// Created by eden on 11/11/2019.
//

#ifndef EX1_BINARYOPERATOR_H
#define EX1_BINARYOPERATOR_H

#include "Expression.h"
#include <iostream>
using namespace std;

class BinaryOperator: public Expression {
protected:
    Expression* bLeft;
    Expression* bRight;
};

#endif //EX1_BINARYOPERATOR_H
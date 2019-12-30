//
// Created by eden on 11/11/2019.
//

#ifndef EX1_UNARYOPERATOR_H
#define EX1_UNARYOPERATOR_H

#include "Expression.h"
#include <iostream>
using namespace std;

class UnaryOperator: public Expression {
protected:
    Expression* exp;
};

#endif //EX1_UNARYOPERATOR_H

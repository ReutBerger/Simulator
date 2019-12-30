//
// Created by eden on 11/11/2019.
//

#ifndef EX1_UMINUS_H
#define EX1_UMINUS_H

#include "UnaryOperator.h"
#include <iostream>
using namespace std;

class UMinus: public UnaryOperator {
public:
    UMinus(Expression* e);

    double calculate();

    virtual ~UMinus();
};

#endif //EX1_UMINUS_H
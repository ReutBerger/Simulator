//
// Created by eden on 11/11/2019.
//

#ifndef EX1_UPLUS_H
#define EX1_UPLUS_H

#include "UnaryOperator.h"
#include <iostream>
using namespace std;

class UPlus: public UnaryOperator {
public:
    UPlus(Expression* e);

    double calculate();

    virtual ~UPlus();
};


#endif //EX1_UPLUS_H

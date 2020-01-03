//
// Created by eden on 11/11/2019.
//

#ifndef EX1_VALUE_H
#define EX1_VALUE_H

#include "Expression.h"

class Value: public Expression {
private:
    double value;

public:
    Value(double vNum);
    virtual double calculate();
};

#endif //EX1_VALUE_H

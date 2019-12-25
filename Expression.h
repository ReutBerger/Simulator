//
// Created by eden on 25/12/2019.
//

#ifndef EX3_EXPRESSION_H
#define EX3_EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

#endif //EX3_EXPRESSION_H

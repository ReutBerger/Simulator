//
// Created by eden on 25/12/2019.
//

#include "Variable.h"

string Variable::getName() {
    return mName;
}

VarDirE Variable::getDirection() {
    return mDirection;
}

float Variable::getVal() {
    return mValue;
}

void Variable::setVal(float val) {
    mValue = val;
}

Variable& Variable::operator++() {
    mValue++;
    return *this;
}

Variable& Variable::operator++(int) {
    Variable* tmp(this);
    ++(*this);
    return *tmp;
}

Variable& Variable::operator--() {
    mValue--;
    return *this;
}

Variable& Variable::operator--(int) {
    Variable* tmp(this);
    --(*this);
    return *tmp;
}

Variable& Variable::operator+=(double const num) {
    mValue += num;
    return *this;
}

Variable& Variable::operator-=(double const num) {
    mValue -= num;
    return *this;
}

double Variable::calculate() {
    return mValue;
}
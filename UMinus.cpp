//
// Created by eden on 11/11/2019.
//

#include "UMinus.h"

// Constructor
UMinus::UMinus(Expression* e) {
    exp = e;
}

double UMinus::calculate() {
    return -1*(exp->calculate());
}

// Destructor
UMinus::~UMinus() {
}
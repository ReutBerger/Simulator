//
// Created by eden on 11/11/2019.
//

#include "UPlus.h"

// Constructor
UPlus::UPlus(Expression* e) {
    exp = e;
}

double UPlus::calculate() {
    return exp->calculate();
}

// Destructor
UPlus::~UPlus() {
}
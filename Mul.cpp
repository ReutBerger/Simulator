//
// Created by eden on 11/11/2019.
//

#include "Mul.h"

// Constructor
Mul::Mul (Expression* left, Expression* right) {
    bLeft = left;
    bRight = right;
}

double Mul::calculate() {
    return (bLeft->calculate() * bRight->calculate());
}

// Destructor
Mul::~Mul() {
}
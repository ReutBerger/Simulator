//
// Created by eden on 11/11/2019.
//

#include "Div.h"

// Constructor
Div::Div (Expression* left, Expression* right) {
    bLeft = left;
    bRight = right;
}

double Div::calculate() {
    double divider = bRight->calculate();

    if (divider == 0)
        throw "division by zero";
    return (bLeft->calculate() / divider);
}

// Destructor
Div::~Div() {
}
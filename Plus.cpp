//
// Created by eden on 11/11/2019.
//

#include "Plus.h"

// Constructor
Plus::Plus(Expression* left, Expression* right) {
    bLeft = left;
    bRight = right;
}

double Plus::calculate() {
    return (bLeft->calculate() + bRight->calculate());
}

// Destructor
Plus::~Plus() {
}
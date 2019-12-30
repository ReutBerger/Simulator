//
// Created by eden on 11/11/2019.
//

#include "Minus.h"

// Constructor
Minus::Minus (Expression* left, Expression* right) {
    bLeft = left;
    bRight = right;
}

double Minus::calculate() {
    return (bLeft->calculate() - bRight->calculate());
}

// Destructor
Minus::~Minus() {
}
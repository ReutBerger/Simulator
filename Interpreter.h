//
// Created by eden on 13/11/2019.
//

#ifndef EX1_INTERPRETER_H
#define EX1_INTERPRETER_H

#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <string>

#include "Expression.h"
#include "Variable.h"

using namespace std;

class Interpreter {
    map<string , double> myMap;
    stack<char> myStack;
    stack<double> calculateStack;
    string output;

public:
    void setVariables(string str);
    Expression* interpret(const char* s);

private:
    void checkArithmeticValidity(const char *s);
    bool isArithmeticOperator(char c);
    bool isOperator(char c);
    void handleOperator(char c);
    int isNumber(const char *s, double &n);
    void handleDigit(double n);
    Variable getVariable(const char *s);
    Expression* calculate();
    void insertCharBefore(string &str, const char *substr);
};

extern Interpreter interpreter;

#endif //EX1_INTERPRETER_H

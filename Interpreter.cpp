//
// Created by eden on 13/11/2019.
//


#include <string.h>

#include "Interpreter.h"
#include "Variable.h"
#include "Mul.h"
#include "Value.h"
#include "Div.h"
#include "Plus.h"
#include "Minus.h"
#include "VarMapClass.h"

#include "UMinus.h"
#include "UPlus.h"
#include <stack>
#include <queue>

Interpreter interpreter;

void Interpreter::setVariables(string str) {
    string delim = ";";
    string delim1 = "=";
    size_t pos, pos1;
    string token;
    int count;

    // Add ';' at the end of the string, in order to loop on all tokens including the last one
    str += ";";

    while ((pos = str.find(delim)) != string::npos) {
        token = str.substr(0, pos);
        pos1 = token.find(delim1);
        string name = token.substr(0, pos1);
        string val  = token.substr(pos1 + 1, token.length());

        // Checking input validity:
        // Checking the input contains "="
        count = std::count(token.begin(), token.end(), '=');
        if (count != 1)
            throw "illegal variable assignment!";
        // Checking the first char of the name input is an alphabet letters or "_"
        if ((!isalpha(name[0]) && name[0] != '_')) {
            throw "illegal variable assignment!";
        }
        // Checking that all the name characters are alphabet letters, numbers, or "_"
        for (uint32_t i = 1; i < name.length(); i++) {
            if (!isalpha(name[i]) && name[i] != '_' && !isdigit(name[i])) {
                throw "illegal variable assignment!";
            }
        }
        // Checking that the value input contains only numbers and maximum one point
        bool point = false;
        for (uint32_t i = (val[0] == '-') ? 1 : 0; i < val.length(); i++) {
            if (!isdigit(val[i]) && (val[i] != '.' || point == true))
                throw "illegal variable assignment!";
            if (val[i] == '.')
                point = true;
        }

        // If the variable is in the map, set the variable value
        Variable *v;
        if (varList.findByName(name, v))
            v->setVal(stof(val));

        str.erase(0, pos + delim.length());
    }
}

void Interpreter::insertCharBefore(string &str, const char *substr) {
    size_t index = 0;
    while (true) {
        // Locate the substring to replace
        index = str.find(substr, index);
        if (index == std::string::npos)
            break;

        // Make the replacement
        // and advance index forward so the next iteration doesn't pick it up as well
         if (index == 0 ||
             (index > 0 && !isalnum(str[index-1]) && str[index-1] != '_' && str[index-1] != ')')) {
            str.insert(index, "0");
            index += 2;
        }
        else
            index += 1;
    }
}

void Interpreter::checkArithmeticValidity(const char *s) {
    for (uint32_t i = 0; i< strlen(s) -1; i++) {
        if (isArithmeticOperator(s[i]) && isArithmeticOperator(s[i+1]))
            throw "illegal math expression";
    }
}

Expression * Interpreter::interpret(const char *s) {
    int incr;
    double n;

    // Check arithmetic operators validity
    checkArithmeticValidity(s);

    string str = s;
    int i = 0;
    string str_new = "";
    while (str[i] != '\0') {
        if(str[i] != ' '){
            str_new += str[i];
        }
        i++;
    }
    // Replace unary operators ('-' or '+') with '0-' or '0+'
    // It will change them to be binary operators and handled below in one single manner
    insertCharBefore(str_new, "-");
    insertCharBefore(str_new, "+");

    // Now, point back to the corrected string
    s = str_new.c_str();

    // Parse the string
    output = "";
    while (*s != '\0') {
        if (isOperator(*s)) {
            handleOperator(*s);
            s++;
        } else if ((incr = isNumber(s, n)) > 0) {
            handleDigit(n);
            s += incr;
        } else {
            Variable v = getVariable(s);
            handleDigit(v.getVal());
            s += v.getName().length();
        }
    }

    while (myStack.size() != 0) {
        // Checking parenthesis validity
        if (myStack.top() == '(' || myStack.top() == ')')
            throw "bad parenthesis input";

        // Pop entire stack to output
        output += myStack.top();
        output += " ";
        myStack.pop();
    }

    return calculate();
}

bool Interpreter::isArithmeticOperator(char c) {
    // If the char is an arithmetic operator, return true.
    // Else, return false.
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool Interpreter::isOperator(char c) {
    // If the char is an operators, return true.
    // Else, return false.
    return (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/');
}

void Interpreter::handleOperator(char c) {
    // Add the operators to the stack in the right order.
    // If necessary, pop and add operators to the output.
    if (c == '(') {
        myStack.push(c);
    }
    else if (c == ')') {
        // until we find '(' on the stack, pop operators.
        while (!myStack.empty() && myStack.top() != '(') {
            output += myStack.top();
            output += " ";
            myStack.pop();
        }
        // Checking parenthesis validity
        if (myStack.empty())
            throw "bad parenthesis input";
        myStack.pop();
    }
    else if (c == '*') {
        if (!myStack.empty() && (myStack.top() == '/' || myStack.top() == '*')) {
            // Pop operator and add it to the output
            output += myStack.top();
            output += " ";
            myStack.pop();
        }
        myStack.push(c);
    }
    else if (c == '/') {
        if (!myStack.empty() && (myStack.top() == '*' || myStack.top() == '/')) {
            // Pop operator and add it to the output
            output += myStack.top();
            output += " ";
            myStack.pop();
        }
        myStack.push(c);
    }
    else if (c == '+' || c == '-') {
        if (!myStack.empty() &&
            (myStack.top() == '+' || myStack.top() == '-' || myStack.top() == '*' || myStack.top() == '/')) {
            // Pop operator, add it to the output and push the new operator to the stack
            output += myStack.top();
            output += " ";
            myStack.pop();
        }
        myStack.push(c);
    }
}

int Interpreter::isNumber(const char *s, double &n) {
    // Change the n to be the number we read and return the number of digits in it.
    uint32_t i = 0;
    bool point = false;
    double m = 1;

    n = 0;

    // If the number is negative, start after it
    if (s[0] == '-' && isdigit(s[1])) {
        m = -1;
        i++;
    }

    // Parse the number until we get a non-digit one
    for (; i < strlen(s); i++) {
        if (!isdigit(s[i]))
            break;

        n *= 10;
        n += s[i] - '0';
    }

    if (s[i] != '.' || point == true)
        return i;

    point = true;

    double q = 1;
    for (i++; i < strlen(s); i++) {
        if (!isdigit(s[i]))
            break;

        q *= 10;
        n += (s[i] - '0') / q;
    }

    n *= m;

    return i;
}

void Interpreter::handleDigit(double n) {
    // Add the numbers to the output string
    string str= to_string(n);
    output += (str + " ");
}

Variable Interpreter::getVariable(const char *s) {
    string str = "";
    const char *p = s;
    while (*p != 0 && !isOperator(*p)) {
        str += *p;
        p++;
    }

    Variable *v;
    if (varList.findByName(str, v))
        return *v;

    throw "Variable was not set";
}

Expression* Interpreter::calculate() {
    double n = 0;
    Expression* e;

    size_t pos;
    string token;

    // If 'c' is a number, push it to the calculate stack.
    while ((pos = output.find(" ")) != string::npos) {
        token = output.substr(0, pos);

        if (isNumber((char *)token.c_str(), n)) {
            calculateStack.push(n);
        }
        else {
            Value *right = new Value (calculateStack.top());
            calculateStack.pop();

            Value *left = new Value (calculateStack.top());
            calculateStack.pop();

            if (token == "*")
                e = new Mul(left, right);
            else if (token == "/")
                e = new Div(left, right);
            else if (token == "+")
                e = new Plus(left, right);
            else if (token == "-")
                e = new Minus(left, right);

            calculateStack.push(e->calculate());
            delete(e);
        }

        output.erase(0, pos + 1);
    }

    return new Value(calculateStack.top());
}

/*
using std::stack;
using std::queue;

bool isOperator(char char1){
    if(char1 == '*' || char1 == '/' || char1 == '+' || char1 == '-' || char1 == '(' || char1 == ')') {
        return true;
    }
    return false;
}
bool isValidVar(string str){
    if(isdigit(str[0]) || str[0] == '_'){
        return false;
    }
    for (unsigned int i = 0; i < str.length(); i++) {
        if (!((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z') || str[i] == '_' || isdigit(str[i]))){
            return false;
        }
    }
    return true;
}
bool isValidNumValue(string str){
    for (unsigned int i = 0; i < str.length(); i++) {
        if(! (isdigit(str[i]) || str[i] == '.')){
            return false;
        }
    }
    return true;
}

void insertOperatorToStack(stack<string>* stk,queue<string>* que, char oper){
    string s;
    s += oper;
    switch (oper) {
        case ')':
            if (!stk->empty()) {
                while (!stk->empty() && stk->top() != "(") {
                    string s2;
                    s2 += stk->top();
                    que->push(s2);
                    stk->pop();
                }
                if (!stk->empty()){
                    stk->pop();
                }else{
                    throw ("Bad input");
                }
            } else {
                throw ("Bad input");
            }
            break;
        case '(':
            stk->push(s);
            break;
        case '*':
        case '/':
            if (!stk->empty()){
                while(!stk->empty() && ( stk->top() == "*" || stk->top() == "/" || stk->top() == "m" || stk->top() == "p")){
                    string s3;
                    s3 += stk->top();
                    que->push(s3);
                    stk->pop();
                }
                stk->push(s);
            } else {
                stk->push(s);
            }
            break;
        case '-':
        case '+':
            if (!stk->empty()){
                while (!stk->empty() && stk->top() != "("){
                    string s4;
                    s4 += stk->top();
                    que->push(s4);
                    stk->pop();
                }
                stk->push(s);
            }else{
                stk->push(s);
            }
            break;
        case 'p':
        case 'm':
            stk->push(s);
        default: //Error
            break;
    }
}

Expression* postfixToExpression(queue<string>* postfix){
    stack<Expression*> stack1;
    Expression* exp;
    Expression* expL =NULL;
    Expression* expR =NULL;
    string temp;
    double numD;
    while (!postfix->empty()){
        temp=postfix->front();
        postfix->pop();
        if (isdigit(temp[0])){
            numD = stod(temp);
            exp = new Value(numD);
            stack1.push(exp);
        }else{
            char op = temp[0];
            if (op == '*' || op == '/' || op == '+' || op == '-') {
                if (!stack1.empty()) {
                    expR = stack1.top();
                    stack1.pop();
                }
                if (!stack1.empty()) {
                    expL = stack1.top();
                    stack1.pop();

                }
                if (expL == NULL || expR == NULL) {
                    throw ("Bad input");
                }
                switch (op) {
                    case '*':
                        exp = new Mul(expL, expR);
                        stack1.push(exp);
                        break;
                    case '/':
                        exp = new Div(expL, expR);
                        stack1.push(exp);
                        break;
                    case '+':
                        exp = new Plus(expL, expR);
                        stack1.push(exp);
                        break;
                    case '-':
                        exp = new Minus(expL, expR);
                        stack1.push(exp);
                        break;
                }
            } else{
                if (!stack1.empty()) {
                    expR = stack1.top();
                    stack1.pop();
                }
                if (expR == NULL) {
                    throw ("Bad input");
                }
                if (op == 'm'){
                    exp = new UMinus(expR);
                    stack1.push(exp);
                } else {
                    // op == 'p'
                    exp = new UPlus(expR);
                    stack1.push(exp);
                }
            }
        }
    }
    return stack1.top();
}

//void Interpreter::setVariables(string str){
//    unsigned int i=0;
//    string var = "";
//    string value= "";
//    while (i < str.length()){
//        while (str[i] != '='){
//            var += str[i];
//            i++;
//        }
//        //Check if var is valid or throw exp
//        if (!isValidVar(var)){
//            throw ("Bad input");
//        }
//        i++;
//        while (str[i] != ';' && i < str.length()){
//            //Check if value is valid or throw exp
//            if (isdigit(str[i]) || str[i] == '.'){
//                value += str[i];
//                i++;
//            } else{
//                throw ("Bad input");
//            }
//        }
//        // Before add new key- check if exist
//
//        if(this->valOfVar.count(var)){
//            this->valOfVar[var] = value;
//        }else{
//            this->valOfVar.insert(pair<string,string>(var,value));
//        }
//        i++;
//        var = "";
//        value= "";
//    }
//}

Expression* Interpreter :: interpret(string str) {
    Expression *exp;
    stack<string> stack1;
    queue<string> queue1;
    string strNum = "";
    string strVar = "";
    unsigned int i = 0;
    while (i < str.length()) {
        if (!isdigit(str[i])) {
            if (isOperator(str[i])) {
                //Check if '-' is unary one
                if (str[i] == '-' || str[i] == '+') {
                    if ((i == 0) || (i > 0 && str[i - 1] == '(')) {
                        if (str[i] == '-') {
                            insertOperatorToStack(&stack1, &queue1, 'm');
                        } else {
                            insertOperatorToStack(&stack1, &queue1, 'p');
                        }
                    } else {
                        insertOperatorToStack(&stack1, &queue1, str[i]);
                    }
                } else {
                    insertOperatorToStack(&stack1, &queue1, str[i]);
                }
                i++;
            }// its var OR " "
            else {
                if (str[i] == ' ') {
                    i++;
                }//its var
                else {
                    //Check correct name of var
                    if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == '_') {
                        while (!isOperator(str[i])) {
                            strVar += str[i];
                            i++;
                        }
                        if (!isValidVar(strVar)) {
                            throw ("Bad input");
                        }
                        //check in the map strVar value -if excise convert it to the value, and put it on the queue1
                        // If the variable is in the map, set the variable value
                        Variable *v;
                        if (varList.findByName(strVar, v))
                            queue1.push(v->getVal());
                            v->setVal(stof(val));

                        if (mapVarName.count(strVar)) {
                            string val = mapVarName.find(strVar)->second;
                            queue1.push(val);
                            strVar = "";
                        } else {
                            throw ("Bad input");
                        }
                    } else {
                        throw ("Bad input");
                    }
                }
            }
            // its number
        } else {
            while (/* check if needed* / i < str.length() && (isdigit(str[i]) || str[i] == '.')) {
                strNum += str[i];
                i++;
            }
            if (isValidNumValue(strNum)) {
                queue1.push(strNum);
                strNum = "";
            } else {
                throw ("Bad input");
            }
        }
    }
    while (!stack1.empty()) {
        string s2;
        s2 += stack1.top();
        queue1.push(s2);
        stack1.pop();
    }
    exp = postfixToExpression(&queue1);
    return exp;
}
*/
//
// Created by eden on 22/12/2019.
//
#include <string>
#include <thread>

#include "SleepCommand.h"
#include "Interpreter.h"

int SleepCommand::execute(vector<string> arr, int index) {
    Interpreter* i1 = new Interpreter();

    Expression* exp = i1->interpret(arr[index].c_str());
    int seconds = exp->calculate();
    this_thread::sleep_for(chrono::milliseconds(seconds));

    delete i1;

    // We handled 1 parameter
    return 1;
}
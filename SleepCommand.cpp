//
// Created by eden on 22/12/2019.
//
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>

#include "SleepCommand.h"
#include "Interpreter.h"

int SleepCommand::execute(vector<string> arr, int index) {
//    int seconds = stoi(arr[index]);
//    sleep(seconds / 1000);
    Interpreter* i1 = new Interpreter();
    Expression* exp = i1->interpret(arr[index].c_str());
    int seconds = exp->calculate();
    this_thread::sleep_for(chrono::milliseconds(seconds));
    return 1;
}
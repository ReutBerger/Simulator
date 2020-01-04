//
// Created by eden on 22/12/2019.
//
#include <string>
#include <thread>

#include "SleepCommand.h"
#include "Interpreter.h"

int SleepCommand::execute(vector<string> arr, int index) {
    this_thread::sleep_for(chrono::milliseconds((int)Calculate(arr[index])));

    // We handled 1 parameter
    return 1;
}
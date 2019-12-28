//
// Created by eden on 22/12/2019.
//
#include <iostream>
#include <string>
#include <unistd.h>

#include "SleepCommand.h"

int SleepCommand::execute(vector<string> arr, int index) {
    int seconds = stoi(arr[index]);
    sleep(seconds / 1000);
    return 1;
}
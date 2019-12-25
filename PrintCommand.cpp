//
// Created by eden on 22/12/2019.
//

#include "PrintCommand.h"

int PrintCommand::execute(vector<string> arr, int index) {
    cout << arr[index] << endl;
    return 1;
}
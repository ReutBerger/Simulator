//
// Created by eden on 28/12/2019.
//

#include "SetVal.h"
#include "Variable.h"
#include "VarMapClass.h"
#include "ConnectCommand.h"

using namespace std;

int SetVal::execute(vector<string> arr, int index) {
    Variable *v;
    if (varList.findByName(arr[index - 2], v)) {
        v->setVal(stof(arr[index]));
        mCC->sendData("set " + v->getNode() + " " + to_string(v->getVal()));
    }

    // We handled 3 parameters
    return 3;
}
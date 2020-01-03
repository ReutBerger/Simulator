//
// Created by eden on 28/12/2019.
//

#include "SetVal.h"
#include "Variable.h"
#include "VarMapClass.h"
#include "ConnectCommand.h"
#include "Interpreter.h"

using namespace std;

int SetVal::execute(vector<string> arr, int index) {
    Variable *v;
    if (varList.findByName(arr[index - 2], v)) {
        string val = arr[index];

        Expression* e = interpreter.interpret(val.c_str());

        v->setVal(e->calculate());

        mCC->sendData("set " + v->getNode() + " " + to_string(v->getVal()) + "\r\n");
    }

    // We handled 1 parameter
    return 1;
}
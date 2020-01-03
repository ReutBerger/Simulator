//
// Created by eden on 22/12/2019.
//

#include "PrintCommand.h"
#include "Expression.h"
#include "Interpreter.h"

int PrintCommand::execute(vector<string> arr, int index) {
    if (arr[index][0] == '"') {
        arr[index].erase(0, 1);
        arr[index].erase(arr[index].size() - 1);

        cout << arr[index] << endl;
    } else {
        Interpreter* i1 = new Interpreter();
        Expression* exp = i1->interpret(arr[index].c_str());
        cout << exp->calculate() << endl;

        delete i1;
    }

    // We handled 1 parameter
    return 1;
}
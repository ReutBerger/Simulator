//
// Created by eden on 19/12/2019.
//

#include <algorithm>

#include "DefineVarCommand.h"
#include "Variable.h"
#include "VarMapClass.h"

using namespace std;

DefineVarCommand cmdDefineVar;

int DefineVarCommand::execute(vector<string> arr, int index) {
    string  name = arr[index];
    VarDirE dir  = (arr[index + 1].compare("->")) ? DIR_IN : DIR_OUT;
    string  sim  = arr[index + 3];
    sim.erase(remove(sim.begin(), sim.end(), '"'), sim.end());

    // Create a new Variable object
    Variable *v = new Variable(name, sim, dir);

    // Add it to the hash maps
    varList.addElement(v, name, sim);

    // We handled 4 parameters
    return 4;
}
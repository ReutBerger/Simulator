//
// Created by eden on 25/12/2019.
//

#include "VarMapClass.h"

// TODO: Make it singleton
VarMapClass varList;

void VarMapClass::addElement(Variable* obj, string name, string node) {
    mapVarName.insert(make_pair(name, obj));
    mapVarNode.insert(make_pair(node, obj));
}

bool VarMapClass::findByName(const string& name, Variable* &obj) {
    VarMapType::const_iterator it = mapVarName.find(name);

    if (it == mapVarName.end())
        return false;

    obj = it->second;
    return true;
}

bool VarMapClass::findByNode(const string& node, Variable* &obj) {
    VarMapType::const_iterator it = mapVarNode.find(node);

    if (it == mapVarNode.end())
        return false;

    obj = it->second;
    return true;
}

//
// Created by eden on 25/12/2019.
//

#include "VarMapClass.h"

VarMapClass varList;

VarMapClass::~VarMapClass() {
    // Clear one of the mapping, so all Variable pointers will be released
    mLock.lock();
    mapVarNode.clear();
    mapVarName.clear();
    mLock.unlock();
}

void VarMapClass::addElement(Variable* obj, string name, string node) {
    mLock.lock();
    mapVarName.insert(make_pair(name, obj));
    mapVarNode.insert(make_pair(node, obj));
    mLock.unlock();
}

bool VarMapClass::findByName(const string& name, Variable* &obj) {
    mLock.lock();
    VarMapType::const_iterator it = mapVarName.find(name);

    if (it == mapVarName.end()) {
        mLock.unlock();
        return false;
    }

    obj = it->second;
    mLock.unlock();

    return true;
}

bool VarMapClass::findByNode(const string& node, Variable* &obj) {
    mLock.lock();
    VarMapType::const_iterator it = mapVarNode.find(node);

    if (it == mapVarNode.end()) {
        mLock.unlock();
        return false;
    }

    obj = it->second;
    mLock.unlock();

    return true;
}
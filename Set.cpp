//
// Created by khaled on 9/27/17.
//

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Set.h"

Set::Set(const std::vector<std::string> elements) {
    for (int i = 0; i < elements.size(); ++i) {
        addElement(elements[i]);
    }
}

std::vector<std::string> Set::getElements() {
    std::vector<std::string> elements;
    for (int i = 0; i < Set::universe.size(); ++i) {
        if (elementsMask & ((long long)1 << i))
            elements.push_back(universe[i]);
    }
    return elements;
}

long Set::indexInUniverse(std::string element) {
    long index = find(universe.begin(), universe.end(), element) - universe.begin();
    if (index < 0 || index >= Set::universe.size())
        throw NotInUniverseException("Element does not exist in Universe set!");
    return index;
}

void Set::addElement(std::string element) {
    long index = indexInUniverse(element);
    elementsMask |= (long long)1 << index;
}

Set Set::intersect(Set set) {
    Set result;
    result.elementsMask = this->elementsMask & set.elementsMask;
    return result;
}

Set Set::unite(Set set) {
    Set result;
    result.elementsMask = this->elementsMask | set.elementsMask;
    return result;
}

Set Set::complement() {
    Set result;
    result.elementsMask = ~this->elementsMask;
    return result;
}

int Set::size() {
    int size = 0;
    for (int i = 0; i < Set::universe.size(); ++i) {
        if (elementsMask & ((long long)1 << i))
            size++;
    }
    return size;
}



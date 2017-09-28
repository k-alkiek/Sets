//
// Created by khaled on 9/27/17.
//

#ifndef SETS_SET_H
#define SETS_SET_H

class Set {
    long indexInUniverse(std::string element);
public:

    unsigned long long elementsMask = 0;
    void addElement(std::string element);
    static std::vector<std::string> universe;
    Set(const std::vector<std::string> elements = {});

    std::vector<std::string>getElements();

    Set intersect(Set set);
    Set unite(Set set);
    Set complement();
    int size();

    struct NotInUniverseException : public std::exception
    {
        std::string s;
        NotInUniverseException(std::string ss) : s(ss) {}
        ~NotInUniverseException() throw () {} // Updated
        const char* what() const throw() { return s.c_str(); }
    };

};


#endif //SETS_SET_H

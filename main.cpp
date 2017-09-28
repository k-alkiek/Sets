#include <iostream>
#include <vector>
#include <limits>
#include "Set.h"



using namespace std;

vector<string> Set::universe;
vector<Set> sets;

void inputUniverse();
void printUniverse();
void reset();

void inputSet();
void printSet(Set set);
int listSets();
void setComplement(int setIndex);
void setUnionWith(int setIndex);
void setIntersectionWith(int setIndex);
void deleteSet(int setIndex);
void showResult(string operation, Set answerSet, int setIndex1, int setIndex2 = -1);

int mainMenu();
int setMenu(int setIndex);
int inputNumber(int low = 1, int up = 64, string errorMsg = "Number of elements must be between 1-64");
void clear();

int main() {
    clear();
    inputUniverse();

    while (mainMenu());
    return 0;
}

int mainMenu() {
    cout << endl;
    cout << "1- Show Universe" << endl;
    cout << "2- Add New Set" << endl;
    cout << "3- List Existing Sets" << endl;
    cout << "4- Reset Universe" << endl;
    cout << "5- Exit" << endl;
    cout << endl << "Enter Option index: ";

    int choice = inputNumber(1, 5, "Enter a valid value");
    clear();
    switch (choice) {
        case 1: printUniverse(); break;
        case 2: inputSet(); break;
        case 3: {
            int setIndex = listSets();
            if (setIndex >=0 && setIndex < sets.size()) {
                while(setMenu(setIndex));
            }
            break;
        }
        case 4: reset(); break;
        case 5: return 0;
        default: return 1;
    }

}

int setMenu(int setIndex) {
    Set set = sets[setIndex];
    cout << "Set " << setIndex + 1 << ": "; printSet(set); cout << endl;

    cout << "1- Complement" << endl;
    cout << "2- Union" << endl;
    cout << "3- Intersection" << endl;
    cout << "4- Delete Set" << endl;
    cout << "5- Back" << endl;
    cout << endl << "Enter Operation index: ";

    int choice = inputNumber(1, 5, "Enter a valid value");
    switch (choice) {
        case 1: setComplement(setIndex); break;
        case 2: setUnionWith(setIndex); break;
        case 3: setIntersectionWith(setIndex); break;
        case 4: deleteSet(setIndex);
        case 5: clear(); return 0;
        default: return 1;
    }

}

void inputUniverse() {
    cout << "Enter Number of elements in the universe:" << endl;
    int n = inputNumber();

    cout << "Enter a list of the elements:" << endl;
    for (int i = 0; i < n; ++i) {
        string element;
        cin >> element;
        Set::universe.push_back(element);
    }
    clear();
}

void printUniverse() {
    cout << "Universe: {";
    for (int i = 0; i < Set::universe.size() ; ++i) {
        cout << Set::universe[i];
        if (i != Set::universe.size() - 1)
            cout << ", ";
    }
    cout << '}';
    cin.clear();
    cin.get();
}

void reset() {
    cout << "Are you sure? Resetting will delete the universe and all existing sets. (y/n)";
    char c;
    cin >> c;
    if (c == 'y' || c == 'Y') {
        Set::universe.clear();
        sets.clear();
        clear();
        inputUniverse();
    }
}

void inputSet() {
    Set set;
    cout << "Enter number of elements in the set" << endl;
    int n = inputNumber(1, (int)Set::universe.size(), "Number of elements must be less than the universe");

    cout << "Enter a list of the elements: (Any elements that are not in the universe will be skipped." << endl;
    for (int i = 0; i < n; ++i) {
        string element;
        cin >> element;
        try {
            set.addElement(element);
        } catch (const Set::NotInUniverseException& e) {
            cout << element << ": " <<e.what();
        }

    }
    sets.push_back(set);

    clear();
    cout << "Set " << sets.size() << " added." << endl;
}

void printSet(Set set) {
    vector<string> elements = set.getElements();
    for (int i = 0; i < elements .size() ; ++i) {
        cout << elements [i];
        if (i != elements.size() - 1)
            cout << ", ";
    }

}

int listSets() {
    for (int i = 0; i < sets.size(); ++i) {
        cout << "Set " << i+1 << ": ";
        printSet(sets[i]);
        cout << endl;
    }

    int n;
    cout << "Enter the index of a set to select it, or any key to go back:" << endl;
    cin >> n;
    n--;
    clear();
    if (n >= 0 && n < sets.size())
        return n;
    return -1;

}

void setComplement(int setIndex) {
    clear();
    Set set = sets[setIndex];
    cout << "Set " << setIndex + 1 << ": "; printSet(set); cout << endl;

    Set answerSet = set.complement();
    showResult("Complement", answerSet, setIndex);
}

void setUnionWith(int setIndex) {
    clear();
    Set set = sets[setIndex];
    cout << "Set " << setIndex + 1 << ": "; printSet(set); cout << endl;
    cout << "Choose The other set to perform the union operation:" << endl;

    int otherSetIndex = listSets();
    if (otherSetIndex== -1) return;

    Set otherSet = sets[otherSetIndex];
    Set answerSet = set.unite(otherSet);
    showResult("Union", answerSet, setIndex, otherSetIndex);
}

void setIntersectionWith(int setIndex) {
    clear();
    Set set = sets[setIndex];
    cout << "Set " << setIndex + 1 << ": "; printSet(set); cout << endl;
    cout << "Choose The other set to perform the intersection operation:" << endl;

    int otherSetIndex = listSets();
    if (otherSetIndex== -1) return;

    Set otherSet = sets[otherSetIndex];
    Set answerSet = set.intersect(otherSet);
    showResult("Intersection", answerSet, setIndex, otherSetIndex);
}

void deleteSet(int setIndex) {
    sets.erase(sets.begin() + setIndex);
}

void showResult(string operation, Set answerSet, int setIndex1, int setIndex2) {
    clear();
    cout << "The result of Set " << setIndex1 + 1 << ' ' << operation;
    if (operation != "Complement")
        cout << " with Set " << setIndex2 + 1;
    cout << " is: " << endl;
    cout << '{'; printSet(answerSet); cout << '}' << endl;

    cout << "Enter 'S' to save the answer or any key to go back: ";
    char c;
    cin >> c;
    if (c == 's' || c == 'S') {
        sets.push_back(answerSet);
    }
    clear();
}

//Input Helpers

int inputNumber(int low, int up, string errorMsg) {
    int n = 0;
    cin >> n;
    while (n < low || n > up || cin.fail()) {
        cout << errorMsg << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> n;
    }
    return n;
}

void clear() {
    //system("clear");
    for (int i = 0; i < 250; ++i) {
        std::cout << endl;
    }
}
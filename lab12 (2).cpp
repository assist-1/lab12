#include <iostream>
#include <vector>
#include <string>

using namespace std;

int& funcForInt(int& x) {
    x++;
    return x;
}

string& funcForString(string& s) {
    s += "!";
    return s;
}

char& funcForChar(char& c) {
    c++;
    return c;
}

template<typename T, typename F>
class myIterator {
    public:
    T parrentIt;
    F trans;
    myIterator(T itr, F fn) {
        parrentIt = itr;
        trans = fn;
    }

    myIterator operator ++(int) {
        parrentIt++;
        return *this;
    }

    
    bool operator ==(myIterator it1) {
        return (parrentIt == it1.parrentIt);
    }

    bool operator !=(myIterator it1) {
        return (parrentIt != it1.parrentIt);
    }

    myIterator operator --(int) {
        parrentIt--;
        return *this;
    }

    decltype(*parrentIt)& operator*() {

        return trans(*parrentIt);
    }

};

int main() {
    
    // Проверка итератора для типа int:

    vector<int> arr{1,2,3,4,5,6};
    int& (*f1)(int&) = &funcForInt;

    typedef myIterator<vector<int>::iterator, int& (*)(int&)> myItInt;

    myItInt mI_begin(arr.begin(), f1);
    myItInt mI_end(arr.end(), f1);

    for (myItInt it = mI_begin; it != mI_end; it++) {
        cout << *it << " ";
    }

    cout << endl;

    // Проверка итератора для типа string:

    vector<string> arr_s{"as","xcv","qwe","gfdg"};

    typedef myIterator<vector<string>::iterator, string& (*)(string&)> myItString;

    string& (*a)(string&) = &funcForString;

    myItString mIS_begin(arr_s.begin(), a);
    myItString mIS_end(arr_s.end(), &funcForString);

    for (myItString it = mIS_begin; it != mIS_end; it++) {
        cout << *it << " ";
    }

    cout << endl;

    // Проверка итератора для типа char:

    vector<char> arr_c{'a','b','v'};

    typedef myIterator<vector<char>::iterator, char& (*)(char&)> myItChar;

    myItChar mI_begin_c(arr_c.begin(), &funcForChar);
    myItChar mI_end_c(arr_c.end(), &funcForChar);

    for (myItChar it = mI_begin_c; it != mI_end_c; it++) {
        cout << *it << " ";
    }

    cout << endl;
}

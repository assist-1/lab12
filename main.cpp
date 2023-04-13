#include"conv_iter.h"
#include <iostream>

#include<vector>
#include<set>

using std::cout;


int Add(int a) {
    return (a + 2);
}

struct Str {
    static int minus(int a) {
        return -a;
    }
};


int main(){

    std::function<int(int)> op1 = Str::minus;
    std::function<int(int)> op2 = Add;

    std::vector<int> v(10);
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = i + 1;
    }

    Conversion_it<std::vector<int>::iterator, int(int)> iter(v.begin(), op1);
    
    for (; iter != v.end(); iter++){
        cout << *iter << ' ';
    }
    cout << '\n';

    std::set <int> s;
    s.insert(1);
    s.insert(2);

    Conversion_it<std::set<int>::iterator, int(int)> iter1(s.begin(), op2);
    
    for (; iter1 != s.end(); iter1++){
        cout << *iter1 << ' ';
    }
    cout << '\n';


    return 0;
}
#include <iostream>
#include <cmath>
#include <vector>

using std::cout;
using std::vector;

bool Prime(int n){
        if ((n==2) || (n==3)) return true;
        for (int i = 2; i<=sqrt(n);++i){
            if (n%i==0) return false;
        }
        return true;
    }

template<class SomeIt>
class OwnIt: public SomeIt{
private:
    SomeIt elem;
    bool (*f)(typename SomeIt::value_type);
public:
    typedef typename SomeIt::value_type value_type;

    OwnIt(SomeIt it, bool(*Prime)(typename SomeIt::value_type)) :    elem(it), f(Prime){
        while (!Prime(*elem)) {
            ++elem;
        }
    }

    value_type operator*() {
        return *elem;
    }
    
    bool operator==(const OwnIt<SomeIt>& IT) {
        return elem == IT.elem;
    }
    
    bool operator!=(const OwnIt<SomeIt>& IT) {
        return !(*this == IT);
    }
    
    OwnIt& operator++(){
        do {
            ++elem;
        } while (Prime(*elem) != true);
        return *this;
    }

    std::ostream& operator<< (std::ostream& out){
        out << elem;
        return out;
    }
};


int main(){
    vector<int> v = {2,4,5,7,11,12};
    OwnIt<vector<int>::iterator> it(v.begin(), Prime);
    while (it != OwnIt<vector<int>::iterator>(v.end(), Prime)) {
        cout << *it << " ";
        ++it;
    }
    cout << "\n";
    return 0;
}
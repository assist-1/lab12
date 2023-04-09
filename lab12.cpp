#include <iostream> 
#include <iterator> 
#include <vector> 

template <typename iter> 
class Functor {  
public: 
    int operator()(iter a) { 
        return *a * 2;  
    } 
}; 

template <typename iter> 
class Transformation { 
private: 
    iter p; 
    Functor<iter> t;
public: 

    Transformation(iter it1, Functor<iter> f) { 
        p = it1;
        t = f;
    } 
    int operator++ () { 
        return *++p; 
    } 

    int operator* () { 
        return t(p);
    } 
    bool operator!= (Transformation<iter> a) { 
        return p != a.p; 
    } 
}; 

int main() { 
    std::vector<int> v({1, 2, 3, 4, 5}); 
    Functor<std::vector<int>::iterator> func;  
    Transformation<std::vector<int>::iterator> c = Transformation<std::vector<int>::iterator>(v.begin(), func);
    Transformation<std::vector<int>::iterator> e = Transformation<std::vector<int>::iterator>(v.end(), func);
    while (c != e) {
        std::cout<< *c << std::endl;
        ++c;
    }
    return 0; 
}
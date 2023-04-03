#include <iostream> 
#include <iterator> 
#include <vector> 


template <typename Iterator, typename T> 
 
class Functor {  
public: 
    T operator () (Iterator a) { 
        return *a + 3;  
    } 
}; 


template <typename Iterator, typename T> 
class Transformation { 
private: 
    Iterator p; 
    Functor<Iterator, T> t;
public: 
    
    Transformation(Iterator it1, Functor<Iterator, T> f) { 
        p = it1;
        t = f;
    } 
    T operator++ () { 
        return *++p; 
    } 
    T operator++ (int) { 
        return *p++; 
    } 
    T operator-- () { 
        return *--p; 
    } 
    T operator-- (int) { 
        return *p--; 
    } 
    T operator* () { 
        return t(p);
    } 
    bool operator!= (Iterator a) { 
        return p != a; 
    } 
    bool operator== (Iterator a) { 
        return p == a; 
    } 
}; 
 
int main() { 
    std::cout << "Example with int: " << std::endl; 
    std::vector<int> vec = {1, 2, 3, 4, 5}; 
    std::vector<int>::iterator y = vec.begin(); 
    Functor<std::vector<int>::iterator, int> q;  
    auto u = Transformation<std::vector<int>::iterator, int>(y, q); 
    while (u != vec.end()) { 
        std::cout << *u << std::endl; 
        ++u; 
        ++y; 
        u = Transformation<std::vector<int>::iterator, int>(y, q); 
    } 
    std::cout << "Example with double: " << std::endl; 
    std::vector<double> vect = {1.23, 2.34, 3.45, 4.56, 5.67, 7.89, 9.01}; 
    std::vector<double>::iterator h = vect.begin(); 
    Functor<std::vector<double>::iterator, double> obj; 
    auto l = Transformation<std::vector<double>::iterator, double>(h, obj); 
    while (l != vect.end()) { 
        std::cout << *l << std::endl; 
        ++l; 
        ++h; 
        l = Transformation<std::vector<double>::iterator, double>(h, obj); 
    } 
    return 0; 
}
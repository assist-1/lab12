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
    T operator- (int n) { 
        return *(p - n); 
    }
    T operator+ (int n) { 
        return *(p + n); 
    }
    T operator* () { 
        return t(p);
    } 
    bool operator!= (Transformation<Iterator, T> a) { 
        return p != a.p; 
    } 
    bool operator== (Transformation<Iterator, T> a) { 
        return p == a.p; 
    } 
}; 
 
int main() { 
    std::cout << "Example with int: " << std::endl; 
    std::vector<int> vec = {1, 2, 3, 4, 5}; 
    Functor<std::vector<int>::iterator, int> q;  
    auto u = Transformation<std::vector<int>::iterator, int>(vec.begin(), q);
    auto k = Transformation<std::vector<int>::iterator, int>(vec.end(), q);
    while (u != k) {
        std::cout<< *u << std::endl;
        ++u;
    }

    std::cout << "Example with double: " << std::endl; 
    std::vector<double> vect = {1.23, 2.34, 3.45, 4.56, 5.67, 7.89, 9.01}; 
    Functor<std::vector<double>::iterator, double> obj; 
    auto l = Transformation<std::vector<double>::iterator, double>(vect.begin(), obj); 
    auto g = Transformation<std::vector<double>::iterator, double>(vect.end(), obj);
    while (l != g) { 
        std::cout << *l << std::endl; 
        ++l; 
    } 
    return 0; 
}
//Output:
//Example with int:
// 4
// 5
// 6
// 7
// 8
// Example with double:
// 4.23
// 5.34
// 6.45
// 7.56
// 8.67
// 10.89
// 12.01
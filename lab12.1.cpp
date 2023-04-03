#include <iostream> 
#include <iterator> 
#include <vector> 


class complex {
  int real;
public:
    complex() {
        real = 0;
    }
    complex(int x) {
        real = x;
    }
    complex operator+ (complex& );
    complex operator- (complex& );
    complex operator* (complex& );
    complex operator/ (complex& );
    bool operator!= (int m) { 
        return this->real != m; 
    } 
    bool operator== (int m) { 
        return this->real == m; 
    } 
    int get_real() {
        return real;
    }
};
std::ostream& operator<< (std::ostream &out, complex& point) {
    out << point.get_real();
    return out; 
}

complex complex::operator+ (complex& obj) {
    complex ob;
    ob.real = this->real + obj.real;
    return ob;
}

complex complex::operator- (complex& obj) {
    complex ob;
    ob.real = this->real - obj.real;
    return ob;
}

complex complex::operator* (complex& obj) {
    complex ob;
    ob.real = this->real * obj.real;
    return ob;
}
complex complex::operator/ (complex& obj) {
    if (obj.real != 0) {
        complex ob;
        ob.real = this->real / obj.real;
        return ob;
    }
    else {
        std::cerr << "Error: division by zero." << std::endl;
        exit(EXIT_FAILURE);
    }
}

template <typename Iterator, typename T> 
 
class Functor { 
private: 
    T d; 
public: 
    void operator () (Iterator a, char b, T c) { 
        switch (b) { 
            case '+': 
                d = *a + c; 
                break; 
            case '-': 
                d = *a - c; 
                break; 
            case '*': 
                d = *a * c; 
                break; 
            case '/': 
                if (c == 0) { 
                    std::cerr << "Error: division by zero." << std::endl; 
                    exit(EXIT_FAILURE); 
                    break; 
                } 
                else { 
                    d = (T) *a / c; 
                    break; 
                } 
            default: 
                std::cerr << "This transformation is not available." << std::endl; 
                exit(EXIT_FAILURE); 
                break; 
        } 
    } 
    T show() { 
        return d; 
    } 
}; 


template <typename Iterator, typename T> 
class Transformation { 
private: 
    Iterator p; 
public: 
    
    
    
    Transformation(Iterator it1, Functor<Iterator, T> f) { 
        
        *it1 = f.show(); 
        p = it1; 
    } 
    T& operator++ () { 
        return *++p; 
    } 
    T& operator++ (int) { 
        return *p++; 
    } 
    T& operator+ (int n) { 
        return *(p + n); 
    } 
    T& operator-- () { 
        return *--p; 
    } 
    T& operator-- (int) { 
        return *p--; 
    } 
    T& operator- (int n) { 
        return *(p - n); 
    } 
    T& operator* () { 
        return *p; 
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
    q(y, '-', 2); 
    auto u = Transformation<std::vector<int>::iterator, int>(y, q); 
    while (u != vec.end()) { 
        std::cout << *u << std::endl; 
        ++u; 
        ++y; 
        q(y, '-', 2); 
        u = Transformation<std::vector<int>::iterator, int>(y, q); 
    } 
    std::cout << "Example with double: " << std::endl; 
    std::vector<double> vect = {1.23, 2.34, 3.45, 4.56, 5.67, 7.89, 9.01}; 
    std::vector<double>::iterator h = vect.begin(); 
    Functor<std::vector<double>::iterator, double> obj; 
    obj(h, '*', 1.12); 
    auto l = Transformation<std::vector<double>::iterator, double>(h, obj); 
    while (l != vect.end()) { 
        std::cout << *l << std::endl; 
        ++l; 
        ++h; 
        obj(h, '*', 1.12); 
        l = Transformation<std::vector<double>::iterator, double>(h, obj); 
    } 
    std::cout << "Example with classes' objects: " << std::endl; 
    complex temp1(1);
    complex temp2(2);
    complex temp3(3);
    std::vector<complex> vectq = {temp1, temp2, temp3};
    std::vector<complex>::iterator j = vectq.begin(); 
    Functor<std::vector<complex>::iterator, complex> ks;
    ks(j, '+', 93); 
    auto i = Transformation<std::vector<complex>::iterator, complex>(j, ks); 
    while (i != vectq.end()) { 
        std::cout << *i << std::endl; 
        ++i; 
        ++j; 
        ks(j, '+', 93); 
        i = Transformation<std::vector<complex>::iterator, complex>(j, ks); 
    } 
    std::cout << "Example with float (mistakes): " << std::endl; 
    std::vector<float> vecf = {1.2, 2.3, 3.4, 4.5, 5.6, 7.8, 9.0}; 
    std::vector<float>::iterator rf = vecf.begin(); 
    Functor<std::vector<float>::iterator, float> jk; 
    jk(rf, '/', 0.0); 
    return 0; 
}
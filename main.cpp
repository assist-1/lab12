#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

bool is_prime(long long n){ 
    if (n == 1) return false;
	for(long long i=2;i<=sqrt(n);i++) {
		if(n%i==0)
			return false;
    }
	return true;
}

template <typename It, typename T>
class Func {
public:
    std::string operator() (It elem) {
        std::string a = "";
        if (is_prime(*elem)) {
            std::ostringstream str1;
            str1 << *elem;
            a = str1.str();
            a += "\n";
        }
        return a;
    }
};

template <typename It, typename T>
class Transform {
    It el;
    Func<It, T> t;
public:
    Transform(It it, Func<It, T> f) {
        el = it;
        t = f;
    }
    std::string operator* () {
        std::ostringstream str2;
        str2 << t(el);
        std::string b = str2.str();
        return b;
    }
    T operator++ () {
        return *++el; 
    }
    T operator-- () {
        return *--el;
    }
    T operator+ (int n) {
        return *(el + n);
    }
    T operator- (int n) {
        return *(el - n);
    }
    bool operator!= (Transform<It, T> elem) {
        return el != elem.el;
    }
    bool operator== (Transform<It, T> elem) {
        return el == elem.el;
    }
};

int main() {

    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; 
    Func<std::vector<int>::iterator, int> q;  
    Transform<std::vector<int>::iterator, int> st = Transform<std::vector<int>::iterator, int>(vec1.begin(), q);
    Transform<std::vector<int>::iterator, int> en = Transform<std::vector<int>::iterator, int>(vec1.end(), q);
    while (st != en) {
        std::cout<< *st;
        ++st;
    }

    return 0;
}
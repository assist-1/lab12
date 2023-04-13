#include <iterator>
#include <functional>

template <class Iterator, typename T>
class Conversion_it {
private:
    Iterator it;
    std::function<T> fun;
public:
    Conversion_it(Iterator it, std::function<T> fun): it(it), fun(fun){}

    typename Iterator::value_type operator*(){
        return fun(*it);
    }
    void operator+=(typename Iterator::value_type n){
        it = it + n;
    }
    void operator-=(typename Iterator::value_type n){
        it = it - n;
    }

    Iterator operator++(){
        return ++it;
    }
    Iterator operator--(){
        return --it;
    }

    Iterator operator++(int){
        return it++;
    }
    Iterator operator--(int){
        return it--;
    }

    Iterator operator+(typename Iterator::value_type n){
        return it + n;
    }
    Iterator operator-(typename Iterator::value_type n){
        return it - n;
    }

    bool operator==(Iterator iter){
        return it==iter;
    }
    bool operator!=(Iterator iter){
        return it!=iter;
    }
    bool operator>(Iterator iter){
        return it>iter;
    }
    bool operator<(Iterator iter){
        return it<iter;
    }
    bool operator>=(Iterator iter){
        return it>=iter;
    }
    bool operator<=(Iterator iter){
        return it<=iter;
    }
};
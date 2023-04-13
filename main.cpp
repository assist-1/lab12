#include <iostream>
#include <iterator>
#include <vector>

/** фактически описанный почтовый итератор должен представлять собой работу функции zip
 * zip должна уметь складывать в один объект несколько объектов разного типа из данных ей контейнеров
 * данная идея требует использования any, а также некого "any_iterator" поскольку это означает реализацию еще одного итератора,
 * в данном варианте будет представлена реализация для случая, когда все контейнеры одного типа
**/


template <class ContainerIterator, class Functor>
class ZipIter: public ContainerIterator{
private:
    ContainerIterator current;
    std::vector<ContainerIterator> others;
    Functor function;
public:
    ZipIter(ContainerIterator firstIter, std::vector<ContainerIterator> others):
            current(firstIter){
        for(auto i: others){
            this->others.push_back(i);
        }
    }

    typedef typename ContainerIterator::value_type value_type;
    value_type operator*(){
        value_type current_value = *(this->current);
        std::vector<value_type> others_values;
        for(int i = 0; i < others.size(); ++i){
            others_values.push_back(*others[i]);
        }
        return function(current_value, others_values);
    };

    void operator++ (){
        current++;
        for(int i = 0; i < others.size(); ++i){
            others[i]++;
        }
    };

    void operator++ (int){
        current++;
        for(int i = 0; i < others.size(); ++i){
            others[i]++;
        }
    };

    void operator-- (){
        current--;
        for(int i = 0; i < others.size(); ++i){
            others[i]--;
        }
    };

    void operator-- (int){
        current--;
        for(int i = 0; i < others.size(); ++i){
            others[i]--;
        }
    };

    ZipIter operator+ (int n){
        ZipIter temp = *this;
        for(int i = 0; i < n; ++i){
            ++temp;
        }
        return temp;
    };

    ZipIter operator- (int n){
        ZipIter temp = *this;
        for(int i = 0; i < n; ++i){
            --temp;
        }
        return temp;
    };

    bool operator== (ZipIter* secondIter){
        if(current != secondIter->current){
            return false;
        }
        for(int i = 0; i < secondIter->others.size(); ++i){
            if(others[i] != secondIter->others[i]){
                return false;
            }
        }
        return true;
    };

    bool operator!= (ZipIter* secondIter){
        if(current == secondIter->current){
            return false;
        }
        for(int i = 0; i < secondIter->others.size(); ++i){
            if(others[i] == secondIter->others[i]){
                return false;
            }
        }
        return true;
    };
};

class FunctorSum{
public:
    int operator() (int a, std::vector<int> b){
        int c = a;
        for(auto i: b){
            c += i;
        }
        return c;
    }
};


int main() {
    typedef std::vector<int>::iterator iterator_type;
    std::vector<int> a{1, 2, 3, 4, 5}, b{10, 10, 10, 10, 10}, c{1, 1, 1, 1, 1};
    std::vector<iterator_type> others; others.push_back(b.begin()); others.push_back(c.begin());
    ZipIter<iterator_type, FunctorSum> summery (a.begin(), others);

    std::cout << *(summery + 2) << "\n";
    for(int i = 0; i < a.size(); ++i){
        std::cout << *summery << ' ';
        summery++;
    }
    return 0;
}

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
    ZipIter* current;
    std::vector<ContainerIterator> others;
    Functor* function;
public:
    ZipIter(ContainerIterator firstIter, ContainerIterator others[], Functor* function):
            current(firstIter), function(function) {
        for(auto i: others){
            this->others.push_back(i);
        }
    }

    typename ContainerIterator::value_type operator*(){
        return function(this->current, this->others);
    };

    ZipIter operator++ (){
        current++;
        for(int i = 0; i < others.size(); ++i){
            others[i]++;
        }
        return *this;
    };

    ZipIter operator-- (){
        current--;
        for(int i = 0; i < others.size(); ++i){
            others[i]--;
        }
        return *this;
    };

    ZipIter operator+ (int n){
        for(int i = 0; i < n; ++i){
            (*this)++;
        }
        return *this;
    };

    ZipIter operator- (int n){
        for(int i = 0; i < n; ++i){
            (*this)++;
        }
        return *this;
    };

    bool operator== (ZipIter* secondIter){
        if(this->current != secondIter->current){
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
        if(this->current == secondIter->current){
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



int main() {
    std::cout << "Hello world!";
    return 0;
}

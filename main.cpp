#include <iostream>
#include <iterator>
#include <vector>
#include <any>

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
    ZipIter(ContainerIterator firstIter, ContainerIterator others[], Functor* function){};
    typename ContainerIterator::value_type operator*(){};
    typename ContainerIterator::value_type operator[] (int n){};
    ZipIter operator+ (){};
    ZipIter operator- (){};
    ZipIter operator++ (){};
    ZipIter operator-- (){};
    bool operator== (ZipIter* secondIter){};
    bool operator!= (ZipIter* secondIter){};
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

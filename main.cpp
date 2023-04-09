#include <iostream>
#include <vector>
#include <cmath>

bool prostoe(int n){
    for (int i = 2; i<=sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}

template <typename Iter>
class FilterIter{
public:
    // Конструктор, принимающий другой итератор и функцию-фильтр
    FilterIter(Iter begin, Iter end, bool(*prostoe)(typename Iter::value_type)):
    begin_(begin), end_(end), prostoe_(prostoe){
        // Ищем первый элемент, удовлетворяющий условию фильтра
        while (begin_ != end_ && !prostoe(*begin_)) {
            ++begin_;
        }
    }

    // Оператор разыменования
    typename Iter::value_type operator*() const {
        return *begin_;
    }

    // Оператор инкремента
    FilterIter<Iter>& operator++() {
        // Ищем следующий элемент, удовлетворяющий условию фильтра
        do {
            ++begin_;
        } while (begin_ != end_ && !prostoe_(*begin_));
        return *this;
    }

    // Операторы сравнения
    bool operator==(const FilterIter<Iter>& other) const {
        return begin_ == other.begin_;
    }

    bool operator!=(const FilterIter<Iter>& other) const {
        return !(*this == other);
    }
private:
    Iter begin_;
    Iter end_;
    bool (*prostoe_)(typename Iter::value_type);
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    // Создаем итератор фильтра, который будет возвращать только нечетные числа
    FilterIter<std::vector<int>::iterator> it(vec.begin(), vec.end(), prostoe);

    // Проходим по контейнеру с помощью итератора фильтра и выводим на экран только нечетные числа
    while (it != FilterIter<std::vector<int>::iterator>(vec.end(), vec.end(), prostoe)) {
        std::cout << *it << " ";
        ++it;
    }
    
    return 0;
}
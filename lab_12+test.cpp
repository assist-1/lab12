

#include <iostream>
#include<vector>
#include<iterator>
template <typename T>
class ReverseIterator {
private:
    typename std::vector<T>::iterator m_iter;
public:
    ReverseIterator(typename std::vector<T>::iterator iter) : m_iter(iter) {}

    ReverseIterator& operator++()
    {
        return --m_iter;
       
    }

    ReverseIterator& operator--()
    {
        return ++m_iter;
        
    }

    ReverseIterator operator++(int)
    {
        return --m_iter;
    }

    ReverseIterator operator--(int)
    {
        return ++m_iter;
    }

    T& operator*()
    {
        return *m_iter;
    }
    ReverseIterator operator+(int n )
    {
        return m_iter-n;
    }

    ReverseIterator operator-(int n )
    {
        return m_iter+n;
    }
    bool operator==(const ReverseIterator& other) const
    {
        return m_iter == other.m_iter;
    }

    bool operator!=(const ReverseIterator& other) const
    {
        return m_iter != other.m_iter;
    }


};

int main()
{
    std::vector<int> myVector = { 1, 2, 3, 4, 5 };

    // Итерирование в прямом порядке
    std::cout << "Forward iteration: ";
    for (auto it = myVector.begin(); it != myVector.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Итерирование в обратном порядке с помощью нашего обратного итератора
    std::cout << "Reverse iteration: ";
    auto it = ReverseIterator<int>(myVector.begin());
    auto it1 = ReverseIterator<int>(myVector.end() - 1);
    while (it1 != it) {

        std::cout << *it1 << " ";
        it1 = it1 + 2;


    }
    std::cout << *it1;
    std::cout << std::endl;



}


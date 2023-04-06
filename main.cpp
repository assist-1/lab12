#include <iostream>
#include <vector>
#include <algorithm>


template<typename InputIterator, typename UnaryFunction>
class TransformIterator : public std::iterator<std::input_iterator_tag,
        typename std::result_of<UnaryFunction(typename InputIterator::value_type)>::type>
{
public:
    TransformIterator(InputIterator it, UnaryFunction func) : m_it(it), m_func(func) {}

    bool operator==(const TransformIterator& rhs) const {
        return m_it == rhs.m_it;
    }

    bool operator!=(const TransformIterator& rhs) const {
        return (m_it != rhs.m_it);
    }

    typename std::result_of<UnaryFunction(typename InputIterator::value_type)>::type operator*() const {
        return m_func(*m_it);
    }

    TransformIterator& operator++() {
        ++m_it;
        return *this;
    }

    TransformIterator operator++(int) {
        TransformIterator tmp(*this);
        ++(*this);
        return tmp;
    }

private:
    InputIterator m_it;
    UnaryFunction m_func;
};


struct doubling {
    int operator()(int x) const {
        return 2*x;
    }
};

int main() {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };

    TransformIterator<std::vector<int>::iterator, doubling> doubling_iter(vec.begin(), doubling());

    std::cout << "Transformed elements: ";
    for (auto it = doubling_iter; it != TransformIterator<std::vector<int>::iterator, doubling>(vec.end(), doubling()); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
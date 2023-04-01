#include <iostream>
#include <vector>
#include <algorithm>


template<typename Iterator, typename Func>
class transform_iterator {
public:
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using reference = typename std::result_of<Func(value_type)>::type;

    transform_iterator(Iterator it, Func func) : it_(it), func_(func) {}

    reference operator*() const {
        return func_(*it_);
    }

    transform_iterator &operator++() {
        ++it_;
        return *this;
    }

    transform_iterator operator++(int) {
        transform_iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const transform_iterator &other) const {
        return it_ == other.it_;
    }

    bool operator!=(const transform_iterator &other) const {
        return it_ != other.it_;
    }

private:
    Iterator it_;
    Func func_;
};


int square(int x) {
    return x * x;
}

int main() {
    std::vector<int> numbers{1, 2, 3, 4, 5};
    transform_iterator<std::vector<int>::iterator, int (*)(
            int)> square_it = transform_iterator<std::vector<int>::iterator, int (*)(int)>(numbers.begin(), square);
    std::for_each(square_it, transform_iterator<std::vector<int>::iterator, int (*)(int)>(numbers.end(), square),
                  [](int x) { std::cout << x << " "; });
    std::cout << std::endl;
    return 0;
}


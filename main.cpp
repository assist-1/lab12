#include <iostream>
#include <vector>

template<typename T>
class ReverseIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    ReverseIterator(std::vector<T>& vec, std::size_t index) : vec_{ vec }, index_{ index } {}

    ReverseIterator& operator++()
    {
        --index_;
        return *this;
    }

    ReverseIterator& operator--()
    {
        ++index_;
        return *this;
    }

    ReverseIterator operator++(int)
    {
        ReverseIterator it(*this);
        --index_;
        return it;
    }

    ReverseIterator operator--(int)
    {
        ReverseIterator it(*this);
        ++index_;
        return it;
    }

    reference operator*()
    {
        return vec_[index_];
    }

    pointer operator->()
    {
        return &vec_[index_];
    }

    bool operator==(const ReverseIterator& other) const
    {
        return index_ == other.index_;
    }

    bool operator!=(const ReverseIterator& other) const
    {
        return index_ != other.index_;
    }

private:
    std::vector<T>& vec_;
    std::size_t index_;
};

int main()
{
    std::vector<int> vec = { 1, 2, 3, 4, 5 };

    for (auto it{vec.rbegin()}; it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}

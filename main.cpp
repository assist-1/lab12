#include <iostream>
#include <vector>

template <typename Iterator, typename Predicate>
class FilterIterator 
{
public:
    FilterIterator(Iterator begin, Iterator end, Predicate pred): begin_(begin), end_(end), pred_(pred) 
    {
        while (begin_ != end_ && !pred_(*begin_)) 
        {
            ++begin_;
        }
    }

    FilterIterator& operator++() 
    {
        while (begin_ != end_ && !pred_(*begin_))
        {
            ++begin_;
        }
        return *this;
    }

    auto operator*() const {return *begin_;}
    bool operator==(Iterator other) const {return begin_ == other;}
    bool operator!=(Iterator other) const {return begin_ != other;}
    bool operator<(Iterator other) const {return begin_ < other;}
    bool operator<=(Iterator other) const {return begin_ <= other;}
    bool operator>(Iterator other) const {return begin_ > other;}
    bool operator>=(Iterator other) const {return begin_ >= other;}

private:
    Iterator begin_;
    Iterator end_;
    Predicate pred_;
};


bool is_odd(int n) 
{
    return n % 2 == 1;
}

int main() 
{
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    FilterIterator i{numbers.begin(), numbers.end(), is_odd};
    
    for (; i < numbers.end(); ++i) 
    {
        std::cout << *i << ' ';
    }
    
    std::cout << '\n';
    return 0;
}

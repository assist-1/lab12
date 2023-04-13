#include <iostream>
#include <vector>

template <typename T>
class reverseIt
{
private:
    T* iter;
public:
    reverseIt(T* it)
    {
        iter = it;
    }
    bool operator==(const reverseIt& other)
    {
        return iter == other.iter;
    }
    bool operator!=(const reverseIt& other)
    {
        return iter!=other.iter;
    }
    reverseIt operator++()
    {
        --iter;
        return *this;
    }
    reverseIt operator--()
    {
        ++iter;
        return *this;
    }
    T& operator*()
    {
        return *iter;
    }
};

int main()
{
    std::vector <int> vec= {1,2,3,4};
    reverseIt <int> r_begin(&vec[vec.size()-1]);
    reverseIt <int> r_end(&vec[0]-1);
    //reverseit <int> it3 = r_begin;
    for(reverseIt <int> it = r_begin; it!=r_end;++it)
    {
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    std::vector <char> vec2 = {'a','b','c'};
    reverseIt <char> r_begin2(&vec2[vec2.size()-1]);
    reverseIt <char> r_end2(&vec2[0]-1);
    for(auto it = r_begin2; it!=r_end2;++it)
    {
        std::cout<<*it<<" ";
    }
    return 0;
}

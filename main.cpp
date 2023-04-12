#include <iostream>
#include <vector>
#include <list>

template <typename type1, typename type2>
class connect_containers {
private:
    type1 begin1_;
    type1 current1_;
    type1 end1_;
    type2 begin2_;
    type2 current2_;
    type2 end2_;
public:
    connect_containers(const type1& begin1, const type1& end1, const type2& begin2, const type2& end2) :
            begin1_(begin1), begin2_(begin2), current1_(begin1), end1_(end1), current2_(begin2), end2_(end2) { }

    connect_containers operator++() {
        if (current1_ != end1_) {
            ++current1_;
        } else {
            ++current2_;
        }
        return *this;
    }

    connect_containers operator--() {
        if (current1_ != end1_) {
            if (current1_ != begin1_)   --current1_;
        } else {
            if (current2_ != begin2_)   --current2_;
            else {
                current1_ = end1_ -1;
            }
        }
        return *this;
    }

    auto operator*() const -> typename std::common_type<typename std::iterator_traits<type1>::value_type,
            typename std::iterator_traits<type2>::value_type>::type {
        if (current1_ != end1_) {
            return *current1_;
        } else {
            return *current2_;
        }
    }

    bool operator==(const connect_containers& other) const {
        return (current1_ == other.current1_ && current2_ == other.current2_);
    }

    bool operator!=(const connect_containers& other) const {
        return !(*this == other);
    }

    connect_containers& operator=(connect_containers a){
        current1_ = a.current_1;
        current2_ = a.current_2;
        return *this;
    }
};

template <typename type1, typename type2>
connect_containers<typename type1::const_iterator, typename type2::const_iterator> connect(const type1& c1, const type2& c2) {
    return connect_containers<typename type1::const_iterator, typename type2::const_iterator>(c1.begin(), c1.end(), c2.begin(), c2.end());
}

int main() {
    std::vector<int> v1 = { 1, 2, 3, 90, 4, 67 };
    std::list<int> l1 = {3, 5, 7};
    std::list<double> l2 = { 4.5, 5.5, 6.5, 8.9, 3.6 };
    auto it = connect(v1, l2);

    for (int i = 0; i < 11; ++i) {
        std::cout << *it << " ";
        ++it;
    }
    --it;
    std::cout << std::endl;
    for (int i = 11; i > 0; --i){
        std::cout << *it << " ";
        --it;
    }
    std::cout << std::endl;
    auto it1 = connect(v1, l1);
    auto it2 = connect(v1, l1);
    ++it2;
    std::cout << *it1 << " " << *it2 << "\n'=': " << (it1 == it2) << " '!=': " << (it1 != it2) << "\n";

    return 0;
}
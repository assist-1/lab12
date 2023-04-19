#include <iostream>
#include <cmath>
#include <vector>
#include <list>

// ### DEFINITIONS ### //

// --FILTER ITERATOR-- //
template<class data_type, class iterator, class function_object>
class FilterIterator {
private:
    iterator current;
    iterator first_spec_elem;
    iterator last_spec_elem;
    iterator begin_it;
    iterator end_it;
    function_object predicate;

    typedef FilterIterator<data_type, iterator, function_object> filter_iterator;

public:
    FilterIterator(iterator begin, iterator end);
    FilterIterator(filter_iterator& prev);

    filter_iterator& begin();
    filter_iterator& end();

    filter_iterator& operator++();
    filter_iterator& operator++(int);
    filter_iterator& operator--();
    filter_iterator& operator--(int);
    data_type        operator*();
    bool             operator!=(filter_iterator& sec);
};

// --FUNCTORS (PREDICATES) examples-- //
class IsPrimeNumberFunction {
public:
    bool operator()(int& number) const;
};
class IsEvenNumberFunction {
public:
    bool operator()(int& number) const;
};
template<class data_type>
class IsPositiveNumberFunction {
public:
    bool operator()(data_type& number) const;
};


int main() {
    // VECTOR //
    std::vector vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    FilterIterator<int, std::vector<int>::iterator, IsPrimeNumberFunction> end1(vec.begin(), vec.end());
    for(FilterIterator<int, std::vector<int>::iterator, IsPrimeNumberFunction> filter(vec.begin(), vec.end()); filter != end1.end(); ++filter) {
        std::cout << *filter << " ";
    }
    std::cout << "\n" << std::endl;

    FilterIterator<int, std::vector<int>::iterator, IsEvenNumberFunction> end2(vec.begin(), vec.end());
    for(FilterIterator<int, std::vector<int>::iterator, IsEvenNumberFunction> filter(vec.begin(), vec.end()); filter != end2.end(); ++filter) {
        std::cout << *filter << " ";
    }
    std::cout << "\n" << std::endl;


    // LIST //
    std::list lst = {1, -2, 3, -4, 5, -6, 7, 8, 9, -10, 11, 12, -13, 14, 15, 16, -17, 18, 19, -20};
    FilterIterator<int, std::list<int>::iterator, IsPositiveNumberFunction<int> > end3(lst.begin(), lst.end());
    for(FilterIterator<int, std::list<int>::iterator, IsPositiveNumberFunction<int> > filter(lst.begin(), lst.end()); filter != end3.end(); ++filter) {
        std::cout << *filter << " ";
    }
    std::cout << "\n" << std::endl;

    FilterIterator<int, std::list<int>::iterator, IsPrimeNumberFunction> end4(lst.begin(), lst.end());
    for(FilterIterator<int, std::list<int>::iterator, IsPrimeNumberFunction> filter(lst.begin(), lst.end()); filter != end4.end(); ++filter) {
        std::cout << *filter << " ";
    }
    std::cout << std::endl;
    return 0;
}

// ### REALIZATIONS ### //

// --Constructor-- //
template<class data_type, class iterator, class function_object>
FilterIterator<data_type, iterator, function_object>::FilterIterator(iterator begin, iterator end) {
    for(current = begin; current != end; current++) {
        if(predicate(*current)) {
            first_spec_elem = current;
            break;
        }
    }
    if(current != end) {
        iterator temp_e = end;
        --temp_e;
        iterator temp_f = first_spec_elem;
        --temp_f;
        for(current = temp_e; current != temp_f; current--) {
            if(predicate(*current)) {
                last_spec_elem = current;
                current = first_spec_elem;
                begin_it = begin;
                end_it = end;
                break;
            }
        }
    }
    else {
        std::cerr << "ERROR: the filter iterator didn't find the required elements!" << std::endl;
        exit(1);
    }
}

// --Copy Constructor-- //
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::FilterIterator(filter_iterator& prev) {
    if(predicate(*prev.current)) {
        this->current         = prev.current;
        this->first_spec_elem = prev.first_spec_elem;
        this->last_spec_elem  = prev.last_spec_elem;
        this->begin_it        = prev.begin_it;
        this->end_it          = prev.end_it;
    }
    else {
        std::cerr << "ERROR: invalid incoming parameter, error in iterator!" << std::endl;
        exit(1);
    }
}

// --Method Begin-- //
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>& FilterIterator<data_type, iterator, function_object>::begin() {
    current = begin_it;
    return *this;
}

// --Method End-- //
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>& FilterIterator<data_type, iterator, function_object>::end() {
    current = end_it;
    return *this;
}

// --Operator "++" prefix-- //
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>& FilterIterator<data_type, iterator, function_object>::operator++() {
    if(current++ != last_spec_elem) {
        for(; current != last_spec_elem; current++) {
            if(predicate(*current))
                return *this;
        }
        return *this;
    }
    else {
        current = end_it;
        return *this;
    }
}

// --Operator "++" postfix-- //
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>& FilterIterator<data_type, iterator, function_object>::operator++(int) {
    filter_iterator temp(*this);
    if(current != last_spec_elem) {
        for(; current != last_spec_elem; current++) {
            if(predicate(*current))
                break;
        }
    }
    else
        current = end_it;
    return temp;
}
// --Operator "--" prefix-- //
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>& FilterIterator<data_type, iterator, function_object>::operator--() {
    if(current != first_spec_elem) {
        for(; current != first_spec_elem; current--) {
            if(predicate(*current))
                return *this;
        }
        return *this;
    }
    else {
        current = begin_it;
        return *this;
    }
}

// --Operator "--" postfix-- //
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>& FilterIterator<data_type, iterator, function_object>::operator--(int) {
    filter_iterator temp(*this);
    if(current != first_spec_elem) {
        for(; current != first_spec_elem; current--) {
            if(predicate(*current))
                break;
        }
    }
    else
        current = begin_it;
    return temp;
}

// --Operator "*"-- //
template<typename data_type, typename iterator, typename function_object>
data_type FilterIterator<data_type, iterator, function_object>::operator*() { return *current; }

// --Operator "!="-- //
template<typename data_type, typename iterator, typename function_object>
bool FilterIterator<data_type, iterator, function_object>::operator!=(FilterIterator<data_type, iterator, function_object>& sec) { return current != sec.current; }


// --Functors (predicates)-- //
bool IsPrimeNumberFunction::operator()(int &number) const {
    if(number <= 1)
        return false;
    if(number == 2)
        return true;
    if(number % 2 == 0)
        return false;
    for(int i = 3; i <= int(std::sqrt(number)); i += 2) {
        if(number % i == 0)
            return false;
    }
    return true;
}

bool IsEvenNumberFunction::operator()(int &number) const { return number % 2 == 0; }

template<typename data_type>
bool IsPositiveNumberFunction<data_type>::operator()(data_type &number) const { return number > 0; }
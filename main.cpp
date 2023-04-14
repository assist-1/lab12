#include <iostream>
#include <cmath>
#include <vector>
#include "filter_iterator.h"

// --Functors (predicates)--
class IsPrimeNumberFunction {
public:
	bool operator()(int&) const;
};
class IsEvenNumberFunction {
public:
	bool operator()(int&) const;
};
template<typename data_type>
class IsPositiveNumberFunction {
public:
	bool operator()(data_type&) const;
}


int main() {
	std::vector vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	for(FilterIterator<int, std::vector<int>::iterator, IsPrimeNumberFunction> filter(vec.begin(), vec.end()); filter != vec.end(); ++filter) {
		std::cout << *filter << std::endl;
	}


	return 0;
}




IsPrimeNumberFunction::operator()(int& number) const {
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

IsEvenNumberFunction::operator()(int& number) const { return number % 2 == 0; }

template<typename data_type>
IsPositiveNumberFunction<data_type>::operator()(data_type& number) const { return number > 0; }
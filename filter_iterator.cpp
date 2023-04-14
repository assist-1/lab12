#include <iostream>

// --Constructor--
template<class data_type, class iterator, class function_object>
FilterIterator<data_type, iterator, function_object>::FilterIterator(iterator& begin, iterator& end) {
	for(current = begin; current != end; current++) {
		if(functor(*current)) {
			first_spec_elem = current;
			break;
		}
	}
	if(current != end) {
		for(current = end - 1; current != first_spec_elem - 1; current--) {
			if(functor(*current)) {
				last_spec_elem = current;
				current = first_spec_elem;
				break;
			}
		}
	}
	else {
		std::cerr << "ERROR: the filter iterator didn't find the required elements!" << std::endl;
		exit(1);
	}
}

// --Copy Constructor--
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::FilterIterator(filter_iterator& prev) {
	if(functor(*prev.current)) {
		this->current           = prev.current;
		this->first_spec_elem   = prev.first_spec_elem;
		this->last_spec_elem    = prev.last_spec_elem;
	}
	else {
		std::cerr << "ERROR: invalid incoming parameter, error in iterator!" << std::endl;
		exit(1);
	}
}

// --Method Begin--
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::begin() {
	current = first_spec_elem;
	return *this;
}

// --Method End--
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::end() {
	current = last_spec_elem;
	return *this;
}

// --Operators--
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::operator++() {
	
}
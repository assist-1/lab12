#include <iostream>
#include "filter_iterator.h"
// --Constructor--
template<class data_type, class iterator, class function_object>
FilterIterator<data_type, iterator, function_object>::FilterIterator(iterator& begin, iterator& end) {
	for(current = begin; current != end; current++) {
		if(predicate(*current)) {
			first_spec_elem = current;
			break;
		}
	}
	if(current != end) {
		for(current = end - 1; current != first_spec_elem - 1; current--) {
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

// --Copy Constructor--
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

// --Method Begin--
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::begin() {
	current = begin_it;
	return *this;
}

// --Method End--
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::end() {
	current = end_it;
	return *this;
}

// --Operators--
template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::operator++() {
	if(current != last_spec_elem) {
		for(; current != last_spec_elem; current++) {
			if(predicate(*current))
				return *this;
		}
		return *this;
	}
	else {
		current = end;
		return *this;
	}
}

template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::operator++(int) {
	filter_iterator temp(*this);
	if(current != last_spec_elem) {
		for(; current != last_spec_elem; current++) {
			if(predicate(*current))
				break;
		}
	}
	else
		current = end;
	return temp;
}

template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::operator--() {
	if(current != first_spec_elem) {
		for(; current != first_spec_elem; current--) {
			if(predicate(*current))
				return *this;
		}
		return *this;
	}
	else {
		current = begin;
		return *this;
	}
}

template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::operator--(int) {
	filter_iterator temp(*this)
	if(current != first_spec_elem) {
		for(; current != first_spec_elem; current--) {
			if(predicate(*current))
				break;
		}
	}
	else
		current = begin;
	return temp;
}

template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::operator*() { return *current; }

template<typename data_type, typename iterator, typename function_object>
FilterIterator<data_type, iterator, function_object>::operator!=(iterator& sec) { return current != sec; }
#ifndef FILTER_ITERATOR
#define FILTER_ITERATOR

template<typename data_type, typename iterator, typename function_object>
class FilterIterator {
private:
	iterator current;
	iterator first_spec_elem;
	iterator last_spec_elem;
	iterator begin_it;
	iterator end_it;
	const function_object predicate;

	typedef FilterIterator<data_type, iterator, function_object> filter_iterator;

public:
	FilterIterator(iterator& begin, iterator& end);
	FilterIterator(filter_iterator& prev);

	FilterIterator<data_type, iterator, function_object>& begin();
	filter_iterator& end();

	filter_iterator& operator++();
	filter_iterator& operator++(int);
	filter_iterator& operator--();
	filter_iterator& operator--(int);
	data_type        operator*();
	bool             operator!=(iterator& sec);
};











#endif
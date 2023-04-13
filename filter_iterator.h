#ifndef FILTER_ITERATOR
#define FILTER_ITERATOR

template<typename data_type, typename iterator, typename function_object>
class FilterIterator {
private:
	iterator current;
	iterator start;
	iterator finish;
	function_object functor;
public:
	typedef FilterIterator<data_type, iterator, function_object> filter_iterator;

	FilterIterator(iterator&, iterator&);
	FilterIterator(filter_iterator&);
	
	filter_iterator& begin();
	filter_iterator  end();

	filter_iterator& operator++();
	filter_iterator& operator--();

};











#endif
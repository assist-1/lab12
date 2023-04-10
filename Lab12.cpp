#include <iostream> 
#include <iterator>
#include <vector> 

#define REQ_FAIL -100

/*
Итератор фильтра: Создайте собственный итератор, который выполняет итерацию по контейнеру и возвращает только те элементы,
которые соответствуют определенным критериям (например, нечетные числа, простые числа и т. д.).
Итератор должен иметь конструктор, который принимает другой итератор и объект функции,
определяющий критерии фильтрации. Протестируйте итератор фильтра с контейнером по вашему выбору.
*/

template<typename T>
class ObjFunc{
	public:
		bool operator()(T t) const{return (t > 0);}
};

template<typename Iterator, typename type>
class CustomIterator{
	protected:
		Iterator iter;
		ObjFunc<type> functor;
		
	public:
		CustomIterator(Iterator it, ObjFunc<type> functr){
			iter = it;
			functor = functr;
		}
		
		type operator*() const {return (functor(*iter)) ? *iter : REQ_FAIL;}
		
		CustomIterator<Iterator, type>& operator++(){
			*iter++;
			return *this;
		}
		CustomIterator<Iterator, type> operator++(int){
			CustomIterator<Iterator, type> result(this->iter, this->functor);
			++*iter;
			return result;
		}
		
		CustomIterator<Iterator, type>& operator--(){
			*iter--;
			return *this;
		}
		CustomIterator<Iterator, type> operator--(int){
			CustomIterator<Iterator, type> result(this->iter, this->functor);
			--*iter;
			return result;
		}
		
		friend bool operator== (CustomIterator<Iterator, type> &lhs, CustomIterator<Iterator, type> &rhs){
			return (lhs.iter == rhs.iter) ? true : false;
		}
		friend bool operator!= (CustomIterator<Iterator, type> &lhs, CustomIterator<Iterator, type> &rhs){
			return (lhs.iter != rhs.iter) ? true : false;
		}
};

int main(){
	ObjFunc<int> functor;
	std::vector<int> vec = {-1, 2, -3, 4, 5};
	
	CustomIterator<std::vector<int>::iterator, int> startIter(vec.begin(), functor);
	CustomIterator<std::vector<int>::iterator, int> endIter(vec.end(), functor);
	
	for (; startIter!=endIter; ++startIter){
		if(*startIter != REQ_FAIL)
			std::cout << *startIter << "\t";
    }
	
	return 0;
}

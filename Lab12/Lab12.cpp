#include<iostream>
#include<iterator>
#include<vector>


template<typename T>
class FuncObject{
	public:
		T mem;
	public:
		FuncObject():mem(0){}
		//FuncObject(int number):mem(number){}
		T operator() (){return mem*mem;}
};

template<class type>
class transformIterator{
		type it;

		FuncObject<typename std::iterator_traits<type>::value_type> mem;
		
	public:
		transformIterator(type first,FuncObject<typename std::iterator_traits<type>::value_type> obj){
			mem = obj;
			it = first;
			
			mem.mem = *it;
			*it = mem();
			
		}
		
		
		typename std::iterator_traits<type>::reference operator*() const {return *it;}

		transformIterator<type>& operator++(){

				it = std::next(it,1);
				mem.mem = *it;
				*it = mem();
				return *this;
		}
		transformIterator<type> operator++(int){
			transformIterator<type> temp = *this;
			it = std::next(it,1);
			mem.mem = *it;
			*it = mem();
			return temp;
		}
		
		transformIterator<type>& operator--(){

				it = std::prev(it,1);
				mem.mem = *it;
				*it = mem();
				return *this;
		}
		transformIterator<type> operator--(int){
			transformIterator<type> temp = *this;
			it = std::prev(it,1);
			mem.mem = *it;
			*it = mem();
			return temp;
		}
		
		
		friend bool operator==(const transformIterator<type>& left,const transformIterator<type>& right){
			if(left.it==right.it) return true;
			else return false;
		}
		friend bool operator!=(const transformIterator<type>& left,const transformIterator<type>& right){
			if(left.it!=right.it) return true;
			else return false;
		}

};






int main(){
	FuncObject<int> a;
	std::vector<int> someVector={1,2,3,4,5,6};
	transformIterator<std::vector<int>::iterator> myIteratorStart(someVector.begin(),a);
	transformIterator<std::vector<int>::iterator> myIteratorEnd(someVector.end(),a);
	for(;myIteratorStart!=myIteratorEnd;myIteratorStart++){std::cout<< *myIteratorStart << std::endl;}
	
	
	return 0;
}
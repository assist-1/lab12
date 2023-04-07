#ifndef TRANSFORM_ITERATOR_H
#define TRANSFORM_ITERATOR_H
#include<iostream>
#include<iterator>
template< class Iterator,typename Function>
class Transform_Iterator{
    private:
    Iterator iter;
    Function function;
    public:
        ~Transform_Iterator(){}
        Transform_Iterator(Iterator it, Function fun): iter(it), function(fun){}
        typename Iterator::value_type operator*(){ 
            return function(*iter);
        }
        void operator+=(typename Iterator::value_type n){
            iter = iter + n;
        }
        void operator-=(typename Iterator::value_type n){
            iter = iter - n;
        }

        Iterator operator++(){
            return ++iter;
        }
         Iterator operator--(){
            return --iter;
        }

         Iterator operator++(int){
            return iter++;
        }
        Iterator operator--(int){
            return iter--;
        }

        Iterator operator+(typename Iterator::value_type n){
            return iter + n;
        }
        Iterator operator-(typename Iterator::value_type n){
            return iter - n;
        }
        
        bool operator==(Iterator iter_){
            return iter==iter_;
        }
        bool operator!=(Iterator iter_){
            return iter!=iter_;
        }
        bool operator>(Iterator iter_){
            return iter>iter_;
        }
        bool operator<(Iterator iter_){
            return iter<iter_;
        }
        bool operator>=(Iterator iter_){
            return iter>=iter_;
        }
        bool operator<=(Iterator iter_){
            return iter<=iter_;
        }
};


class Function{
    public:
    int operator()(int a) { return a *= 2; }
};


#endif

#include <iostream>
#include <deque>



typedef std::deque<int> container;
typedef container::iterator iterator;


template<class Iterator>
class functor;


template<class Iterator>
class Transform_Iterator: public Iterator
{
  functor<Iterator>*  func;
  Iterator            curr;
  public:
    typedef typename Iterator::value_type value_type;
    Transform_Iterator(Iterator iter, functor<Iterator>* obj)
      : curr(iter), func(obj) {};

    value_type operator* () {return (*func)(curr);}
    value_type operator[] (int a) {return *((*this)+a);}
    Transform_Iterator operator+ (int a) {return Transform_Iterator(curr+a, func);}
    friend Transform_Iterator operator+ (int a, Transform_Iterator& iter) {return (iter+a);}
    Transform_Iterator operator- (int a) {return Transform_Iterator(curr-a, func);}
    Transform_Iterator operator++ () {++curr; return *this;}
    Transform_Iterator operator++ (int) {Transform_Iterator temp=*this; ++curr; return temp;}
    Transform_Iterator operator-- () {--curr; return *this;}
    Transform_Iterator operator-- (int) {Transform_Iterator temp=*this; --curr; return temp;}
    bool operator== (Transform_Iterator& it) {return ((curr==it.curr)&&(func==it.func));}
    bool operator!= (Transform_Iterator& it) {return !(*this==it);}
};



template<class Iterator>
class functor
{
    using value_type = typename Transform_Iterator<Iterator>::value_type;
  public:
    virtual value_type operator() (Iterator)  = 0;
};

template<class Iterator>
class linear: public functor<Iterator>
{
  float a, b;
  using value_type = typename Transform_Iterator<Iterator>::value_type;
  public:
    value_type operator() (Iterator iter) 
    {
      return ((*iter)*((value_type)b)+((value_type)a));
    }
    linear (float a=0, float b=1): a(a), b(b) {}
};

template<class Iterator>
class square: public functor<Iterator>
{
  using value_type = typename Transform_Iterator<Iterator>::value_type;
  public:
    value_type operator() (Iterator iter) 
    {
      return ((*iter)*(*iter));
    }
};


std::ostream& operator<< (std::ostream& out, container v)
{
  out << "[" << * v.begin();
  for (iterator i = v.begin()+1; i != v.end(); ++i)
  {
    out << ", " << *i;
  }
  out << "]";
  return out;
}


void fill_container (container& vec)
{
  std::cout << "Vector: " << vec
        << "\n\nIf you want change it enter 1  ==> ";
  int key;
  std::cin >> key;
  if (key==1)
  {
    std::cout << "\nEnter number of elements (1 or more)  ==> ";
    int size;
    std::cin >> size;
    if (size<1) 
    {
      std::cerr << "Size mustn\'t be less than 1.\n";
      exit(1);
    }
    vec.clear(); vec.resize(size);
    std::cout << "Enter elements:\n";
    for (iterator i = vec.begin(); i != vec.end(); ++i)
    {
      std::cin >> *i;
    }
    std::cout << "\nNew vector: " << vec << "\n\n";
  }
}


int main ()
{
  container a{1,2,3,4,5};
  fill_container(a);
  linear<iterator> lin(0,2); 
  square<iterator> sqr;
  functor<iterator>* func = &sqr;
  Transform_Iterator<iterator> It(a.begin(), func), end(a.end(), func);
  
  std::cout << "[" << *(It++);
  for (;It!=end; It++)
  {
    std::cout << ", " << *It;
  }
  std::cout << "]";
  
  return 0;
}
/*

Создайте пользовательский итератор, который объединяет элементы из двух или более контейнеров в один итератор. Итератор должен иметь конструктор, который берет итераторы из каждого контейнера, а стандартные функции итератора должны объединять элементы из каждого контейнера в один элемент. Протестируйте свой итератор с двумя контейнерами по вашему выбору.

*/


#include <iostream>
#include <vector>
#include <iterator>
#include <list>

using std::vector;
using std::cin;
using std::cout;
using std::iterator;
using std::list;

class CustomIter 
{
public:
  template<typename... Args>
  CustomIter(Args... containers) //все контейнеры
  {
    this->fill_containers(containers...);
  };

  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;

    Iterator(
      list<vector<int>>::iterator c_it,
      list<vector<int>>::iterator c_end,
      vector<int>::iterator v_it
    ) : c_it(c_it), c_end(c_end), v_it(v_it) {}

    reference operator*() const { return *v_it; }

    Iterator& operator++() {
      v_it++;
      if (v_it == c_it->end())
      {
        c_it++;
        if (c_it != c_end) {
          v_it = c_it->begin();
        }
      }
      return *this;
    }
    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
    friend bool operator== (const Iterator& a, const Iterator& b) {
      return a.c_it == b.c_it && a.v_it == b.v_it;
    };
    friend bool operator!= (const Iterator& a, const Iterator& b) {
      return a.c_it != b.c_it || a.v_it != b.v_it;
    };
  private:
    list<vector<int>>::iterator c_it;
    list<vector<int>>::iterator c_end;
    vector<int>::iterator v_it;
  };

  Iterator begin() {
    return Iterator(containers.begin(), containers.end(), containers.front().begin());
  }
  Iterator end() {
    return Iterator(containers.end(), containers.end(), containers.back().end());
  }
private:
  list<vector<int>> containers;

  void fill_containers(vector<int> cont)
  {
    this->containers.push_back(cont);
  };

  template<typename... Args>
  void fill_containers(vector<int> cont, Args... containers)
  {
    this->containers.push_back(cont);
    this->fill_containers(containers...);
  };
};

//====================================


int main() {
  vector<int> a = {2, 5};
  vector<int> b = {6, 7};
  CustomIter c(a, b, a);
  
  for (auto i = c.begin(); i != c.end(); ++i) {
    cout << *i << " ";
  }
}
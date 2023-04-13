#include <iostream>
#include <vector>

using namespace std;

template <class T> class R_Iterator {
  T iterator;

public:
  R_Iterator(T i) : iterator(i) {}
  ~R_Iterator() {}

  typename T::value_type operator*() { return *iterator; }

  T operator++() { return iterator--; }
  T operator++(int) { return iterator--; }

  T operator--() { return iterator++; }
  T operator--(int) { return iterator++; }

  void operator+=(int n) { iterator -= n; }
  void operator-=(int n) { iterator += n; }

  bool operator==(T i) { return iterator == i; }
  bool operator!=(T i) { return iterator != i; }

  friend bool operator==(T i, R_Iterator<T> &self);
  friend bool operator!=(T i, R_Iterator<T> &self);

  bool operator>(T i) { return iterator > i; }
  bool operator>=(T i) { return iterator >= i; }
  bool operator<(T i) { return iterator < i; }
  bool operator<=(T i) { return iterator <= i; }
};

template <class T> bool operator==(T i, R_Iterator<T> &self) {
  return i == self.iterator;
}

template <class T> bool operator!=(T i, R_Iterator<T> &self) {
  return i != self.iterator;
}

int main() {
  vector<int> v = {0, 1, 2, 3, 4, 5, 6, 8};
  R_Iterator<vector<int>::iterator> iter(v.end() - 1);
  for (; iter >= v.begin(); iter++){
    cout << *iter << '\t';
  }
  cout << endl;
  return 0;
}

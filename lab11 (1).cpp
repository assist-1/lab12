/*

Взаимодействие итераторов: Продемонстрируйте совместимость итераторов между различными типами контейнеров, такими как вектор и двухсторонняя очередь. Напишите программу, которая создает вектор целых чисел, а затем использует итераторы для копирования элементов вектора в очередь.

*/

#include <iostream>
#include <vector>
#include <deque>

using std::deque;
using std::vector;
using std::cout;

template <typename T, typename Q>
void vec_to_deq(vector<T> &vec, deque<Q> &queue) {
  for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        queue.push_back(*iter);
    }
  
  auto it = queue.begin();
  while (it != queue.end()) {
    cout << ' ' << *it++;
  }
  cout << '\n';
}

//=========================================

int main() {
  vector<int> vec = {100, 10, 1, 456};
  deque<int> deq;
  
  vec_to_deq(vec, deq);
}
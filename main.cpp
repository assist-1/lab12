#include <iostream>
#include <string>
#include <cmath>
#include <vector>

template<typename Iterator>
class FilterFunction {
 private:
  int result;
 public:
  FilterFunction(Iterator &iterator, std::string &functionName) {
    if (functionName == "prime numbers") {
      bool flag = true;
      for (int i = 2; i < int(sqrt(*iterator)) + 1; ++i) {
        if (*iterator % i == 0) {
          flag = false;
          break;
        }
      }
      if (flag) {
        result = *iterator;
      } else {
        result = 4;
      }
    } else if (functionName == "odd numbers") {
      if (*iterator % 2 == 1) {
        result = *iterator;
      } else {
        result = 4;
      }
    }
  }

  int returnResult() {
    if (result == 4) {
      return 4;
    } else {
      return result;
    }
  }
};

template<typename Iterator>
class FilterIterator {
 private:
  Iterator temporary;
 public:
  FilterIterator(Iterator &iterator, FilterFunction<Iterator> &filterFunction) {
    temporary = iterator;
    *iterator = filterFunction.returnResult();
  }
  int operator++() {
    return *++temporary;
  }
  int operator*() {
    return *temporary;
  }
};

int main() {
  std::vector<int> vector(20);
  for (int i = 0; i < 20; ++i) {
    vector[i] = i + 1;
  }
  std::string firstFunctionName = "prime numbers", secondFunctionName = "odd numbers";

  for (auto i = vector.begin(); i != vector.end(); ++i) {
    auto firstIterator = i;
    FilterFunction<std::vector<int>::iterator> function(firstIterator, firstFunctionName);
    FilterIterator<std::vector<int>::iterator> secondIterator(firstIterator, function);
    if (*secondIterator != 4) {
      std::cout << *secondIterator << ' ';
    }
    ++secondIterator;
    ++firstIterator;
  }

  std::cout << std::endl;

  for (auto i = vector.begin(); i != vector.end(); ++i) {
    auto firstIterator = i;
    FilterFunction<std::vector<int>::iterator> function(firstIterator, secondFunctionName);
    FilterIterator<std::vector<int>::iterator> secondIterator(firstIterator, function);
    if (*secondIterator != 4) {
      std::cout << *secondIterator << ' ';
    }
    ++secondIterator;
    ++firstIterator;
  }
  return 0;
}

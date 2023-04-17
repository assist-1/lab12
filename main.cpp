#include <iostream>
#include <vector>
template <class Cont1, class Cont2, class T>
class MergeIter{
private:
    Cont1* c1;
    Cont2* c2;
    typename Cont1::iterator it1;
    typename Cont2::iterator it2;
public:
    MergeIter(Cont1* First, Cont2* Second){
        it1 = (*First).begin();
        it2 = (*Second).begin();
        c1 = First;
        c2 = Second;
  }
    MergeIter& operator++(){
        if (it1 != (*c1).end()) {
            it1++;
        }
        else {
            if (it2 != (*c2).end()){
                it2++;
            }
            else    {
                std::cerr << "error" << std::endl;
            }
        }
        return *this;
    }
    MergeIter& operator--() {
        if (it1 != (*c1).end()) {
            if (it1 != (*c1).begin){
                it1--;
        }
            else {
                std::cerr << "Error" << std::endl;
            }
        }
        else {
            if (it2 != (*c2).end()){
                if (it2 != (*c2).begin()){
                    it2--;
                }
                else {
                    std::cerr << "Error" << std::endl;
                }
            }

        }
    return *this;
  }
    bool operator==(MergeIter& other) {
        return (this->it1 == other.it1 && this->it2 == other.it2);
  }
    T operator*(){
        if (this->it1 != (*c1).end()){
            return (*it1);
        }
        else if (this->it2 != (*c2).end()){
            return (*it2);
        }
        else{
            std::cerr << "Error" << std::endl;
            exit(1);
        }
  }
  //MergeIter& end() {
    //it1 = (*c1).end();
    //it2 = (*c2).end();
    //return *this;
  //}
};
int main() {
    std::vector<float> vec1 = {5,1,5,123.1,132.5,15,15};
    std::vector<float> vec2 = {1,7,10,16.1,1.2,100};
    MergeIter< std::vector<float>, std::vector<float>, float > new_iter1(&vec1, &vec2);
    MergeIter< std::vector<float>, std::vector<float>, float > new_iter2(&vec1, &vec2);
    std::cout << (new_iter1 == new_iter2) << std::endl;

    for (int i = 0; i < 13; ++i){
        std::cout << *new_iter1 << " ";
        ++new_iter1;
    }
    std::cout << "\n";
    std::cout << (new_iter1 == new_iter2) << std::endl;
}

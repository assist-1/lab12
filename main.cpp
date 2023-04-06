#include <iostream>
#include <vector>
#include <deque>

template <class first_container, class second_container>
class new_iter{
private:
    typename first_container::iterator current_1;
    typename second_container::iterator current_2;
    first_container* first;
    second_container* second;
public:
    new_iter(first_container* A, second_container* B){
        first = A;                      second = B;
        current_1 = (*A).begin();       current_2 = (*B).begin();
    };

    new_iter operator++(){
        if (current_1 != (*first).end())
            current_1++;
        else
            if (current_2 != (*second).end())
                current_2++;
            else
                std::cerr << "error";
        return *this;
    }

    new_iter operator--(){
        if (current_1 != (*first).end())
            if (current_1 != (*first).begin())
                current_1--;
            else
                std::cerr << "error";
        else
            if (current_2 != (*second).begin())
                current_2--;
            else
                current_1 = (*first).end() - 1;
        return *this;
    }

    int operator*(){
        if (current_1 != (*first).end())
            return (*current_1);
        else
            return (*current_2);
    }

    new_iter& operator=(typename first_container::iterator A){
        current_2 = (*second).begin();
        current_1 = A;
        return *this;
    }

    new_iter& operator=(typename second_container::iterator A){
        current_1 = (*first).end();
        current_2 = A;
        return *this;
    }

    new_iter& operator=(new_iter A){
        current_1 = A.current_1;
        current_2 = A.current_2;
        return *this;
    }

    bool operator==(const new_iter& A){
        return (this->current_1 == A.current_1 and this->current_2 == A.current_2);
    }

    new_iter operator+(int n){
        if (n > (*first).end() - current_1) {
            if (n - ((*first).end() - current_1) > (*second).end() - (*second).begin())
                std::cerr << "\n\nerror\n\n";
            else {
                current_2 = current_2 + n - ((*first).end() - current_1);
                current_1 = (*first).end();
            }
        } else
            current_1 += n;
        return *this;
    }

    new_iter operator-(int n){
        if ((*first).end() != current_1){
            if (current_1 - (*first).begin() < n)
                std::cerr << "\n\nerror\n\n";
            else
                current_1 -= n;
        } else {
            if (n > current_2 - (*second).begin()) {
                current_1 = (*first).end() - (current_2 - (*second).begin());
                current_2 = (*second).begin();
            } else
                current_2 -= n;
        }
        return *this;

    }
};

int main() {
    std::vector<int> A = {2, 1, 3, 4 ,5, 9};
    std::deque<int> B;
    B.push_back(12); B.push_back(14); B.push_back(10); B.push_back(1); B.push_back(2); B.push_back(7);

    // vector: (2   1   3   4   5   9)
    // deque:  (12  14  10  1   2   7)
    // container: (2   1   3   4   5   9   12  14  10  1   2   7)



    new_iter<std::vector<int>, std::deque<int>> iter_1 (&A, &B);
    std::cout << "Demonstration ++\n";
    for (int i = 0; i < 10; ++i){
        std::cout << *iter_1 << " ";
        ++iter_1;
    }
    std::cout << "\n\nDemonstration --\n";
    for (int i = 10; i > 0; --i){
        std::cout << *iter_1 << " ";
        --iter_1;
    }
    std::cout << "\n\nDemonstration ==\n";
    new_iter<std::vector<int>, std::deque<int>> iter_2 (&A, &B);
    std::cout << (iter_1 == iter_2) << "\n\nDemonstration =\n";
    iter_1 = A.begin();
    std::cout << *iter_1 << "\n\nDemonstration +\n";
    iter_1 = iter_1 + 5;
    std::cout << *(iter_1) << " " << *(iter_1 + 3) << "\n\nDemonstration -\n";
    iter_1 = iter_1 - 1;
    std::cout << *(iter_1) << " " << *(iter_1) - 4;
}

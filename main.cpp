#include <iostream>
#include <vector>
#include <deque>
using namespace std;

template <class A, class B>
class CustIt {
private:
    typename A::iterator a;
    typename B::iterator b;
    A* first;
    B* sec;
public:
    CustIt(A* c, B* d) {
        a = (*c).begin();
        b = (*d).begin();
        first = c;
        sec = d;
    }CustIt operator--(int) {
        if (a != (*first).begin()) a--;
        if (b != (*sec).begin()) b--;
        return *this;
    }CustIt operator++(int) {
        if (a != (*first).end()) a++;
        if (b != (*sec).end()) b++;
        return *this;
    }CustIt operator+(int n) {
        if (n < (*first).end() - a) a += n;
        else a = (*first).end();
        if (n < (*sec).end() - b) b += n;
        else b = (*sec).end();
        return *this;
    }CustIt operator-(int n) {
        if (n < a - (*first).begin()) a -= n;
        else a = (*first).begin();
        if (n < b - (*sec).begin()) b -= n;
        else b = (*sec).begin();
        return *this;
    }CustIt& operator=(typename A::iterator h) {
        b = (*sec).begin();
        a = h;
        return *this;
    }CustIt& operator=(typename B::iterator h) {
        a = (*first).begin();
        b = h;
        return *this;
    }CustIt& operator=(CustIt h) {
        a = h.a;
        b = h.b;
        return *this;
    }pair<int, int> operator*() {
        return make_pair(*a, *b);
    }bool operator==(CustIt h) {
        return ((this->a == h.a) and (this->b == h.b));
    }int operator-(CustIt h) {
        return (max(this->a - h.a, this->b - h.b));
    }
};

int main()
{
    vector<int> a{1, 2, 3, 4, 5, 6, 7};
    deque<int> b{ 3, 4, 5, 6 };
    CustIt<vector <int>, deque<int>> gv(&a, &b);
    CustIt<vector <int>, deque<int>> gvh(&a, &b);
    gv--;
    gv++;
    gv = gv + 2;
    gv = gv - 6;
    pair<int, int> с = *gv;
    cout << (gv == gvh);
    gv++;
    int d = gv - gvh;
    cout << d;
}

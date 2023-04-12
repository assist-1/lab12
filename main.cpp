#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

template<typename t>
class user_it{
private:
  typename t :: iterator a;
  typename t :: iterator b;
  typename t :: iterator curr;
public:
  user_it(typename t :: iterator tmp1, typename t :: iterator tmp2){
    a = tmp1; b = --tmp2; curr = tmp1;
  };

  void operator++ (){if (curr != b)++curr;
    else cout<<"Error: end reached\n";};
  void operator-- (){if (curr != a)--curr;
    else cout<<"Error: begining reached\n";};
  typename t :: value_type operator* (){ return *curr;};
  typename t :: iterator cur(){ return curr; };
};

int main(){
  vector <char> task = {'3','1','2','4','5'};
  vector <char> :: iterator it_A = task.begin();
  vector <char> :: iterator it_B = task.end();
  user_it <vector<char>> example{it_A, it_B};
 cout << *example << endl;
  --example;
  cout << *example.cur() << endl;
  ++example;
  cout << *example.cur() << endl;
  ++example;
  cout << *example.cur() << endl;
  ++example;
  cout << *example.cur() << endl;
  ++example;
  cout << *example.cur() << endl;
  ++example;
  cout << *example.cur() << endl;
  return 0;
}

#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

class user_it{
private:
  vector<int> :: iterator a;
  vector<int> :: iterator b;
  vector<int> :: iterator curr;
  bool check_a = true;
  bool check_b = false;
public:
  user_it(vector<int> :: iterator tmp1, vector<int> :: iterator tmp2){
    a = tmp1; b = --tmp2; curr = tmp1;
    if(a == b){
      check_b = true;
    }
  };

  void operator++ (){if (curr != b)++curr;
    else cout<<"Error: end reached\n";};
  void operator-- (){if (curr != a)--curr;
    else cout<<"Error: begining reached\n";};
  int operator* (){ return *curr;};
  vector<int> :: iterator cur(){ return curr; };
};

int main(){
  vector <int> task = {1,2,3,4,5};
  vector <int> :: iterator it_A = task.begin();
  vector <int> :: iterator it_B = task.end();
  user_it example = user_it(it_A, it_B);
  cout << *example.cur() << endl;
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

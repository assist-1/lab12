#include"Transform_Iterator.h"
#include<vector>
#include<set>
int main(){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Function1 f;
    Transform_Iterator<std::vector<int>::iterator, Function1> ti(v.begin(),f);
    for(Transform_Iterator<std::vector<int>::iterator, Function1> ti(v.begin(),f);ti!=v.end();ti++){
        std::cout<<*ti<<'\n';
    }
    std::cout<<'\n';
    std::set<std::string> s = {"a", "b", "c", "d"};
    Function2 f2;
    Transform_Iterator<std::set<std::string>::iterator, Function2> i(s.begin(),f2);
    for(Transform_Iterator<std::set<std::string>::iterator, Function2> i(s.begin(),f2); i!=s.end();i++){
        std::cout<<*i<<'\n';
    }
    std::cout<<'\n';
    return 0;
}
#include"Transform_Iterator.h"
#include<vector>
int main(){
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int>::iterator i=v.begin();
    Function f;
    Transform_Iterator<std::vector<int>::iterator, Function> ti(i,f);
    for(Transform_Iterator<std::vector<int>::iterator, Function> ti(i,f);ti!=v.end();ti++){
        std::cout<<*ti<<'\n';
    }
    return 0;
}
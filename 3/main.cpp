#include <iostream>
#include "cpplab.h"


template<typename T>
void print_V(const cpplab::vector<T> &v)
{
    if(v.size() != 0){
    std::cout << "[";
    for(size_t i(0); i<v.size()-1; i++)
        std::cout << v[i] << "," ;
    std::cout << v[v.size()-1]<< "]\n";
    }
}

int main(){

    cpplab::vector<int> v;
    v.emplace_back(1,2,3);

    cpplab::vector<int> u(v);
    cpplab::vector<int> vv;
    u.pop_back();
    vv = u;
    print_V(v);
    v = std::move(u);
    print_V(v);

    std::vector<int> w = {1, 1};

    std::cout<< v * w<< "\t" << w * v << "\t"<< v*vv <<"\n";


}
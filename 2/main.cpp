#include <iostream>
#include "add.h"
#include "hyperqube.h"

int main(){
    {
    int a(5);
    double b(5.5);
    auto var = add(&a, &b);
    std::cout<< var << "\n";
    }
    
    {
    const char string_one[] = "Hello ";
    const char string_two[] = "World!";
    printf("%s\n", add(string_one, string_two));
    }

    {
        hyperqube<2,3> cube;
        std::cout << cube.volume << "\n";
    }
    
    auto var = add_total(1,1.5,0.3f);
    std::cout<< var << '\n';
}
    


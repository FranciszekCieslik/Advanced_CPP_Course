#include <iostream>
#include "thread_pool.cpp"

int main()
{
    {
        Thread_pool pool{5};
 
        for (auto i = 0; i < 6; ++i)
        {
            pool.add_task([i]()-> double {return double(i*2);});
            pool.get_var();
        }
        std::cout<< '\n' << "average: "<<pool.average() << '\n';
    }
}
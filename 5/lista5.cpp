#include <iostream>
#include <pthread.h>
#include <mutex>
#include <thread>
#include <future>

pthread_t my_id() 
{
    return pthread_self();
}

void my_print(std::string str)
{
    std::lock_guard<std::mutex> lock(std::mutex mtx);
    std::cout << "Thread: " << my_id() << ":\t" << str << '\n';
}

void asyncFunction(int depth, std::launch policy) {
    my_print("Start asyncFunction, Depth: " + std::to_string(depth));

    if (depth > 0) {
        std::future<void> fut = std::async(policy, asyncFunction, depth - 1, policy);
        fut.get(); 
    }

    my_print("End async Function, Depth: " + std::to_string(depth));
}

int main() {
    my_print("Calling asyncFunction with std::launch::async policy: ");
    asyncFunction(3, std::launch::async);
    std::cout<<'\n';
    my_print("Calling asyncFunction with std::launch::deferred policy: ");
    asyncFunction(3, std::launch::deferred);

    return 0;
}
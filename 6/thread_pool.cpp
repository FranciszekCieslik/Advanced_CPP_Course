#include "thread_pool.h"


Thread_pool::Thread_pool(std::size_t numThreads)
{
    start(numThreads);
};

Thread_pool::~Thread_pool()
{
    stop();
};

void Thread_pool::add_task(std::function<double()> task)
{
    auto wrapper = std::make_shared<std::packaged_task<decltype(task()) ()>>(std::move(task));

    {
        std::unique_lock<std::mutex> lock{mEventMutex};
        mTasks.emplace([=] {
            (*wrapper)();
        });
    }

    mEventVar.notify_one();
    futuresTotalScore += (wrapper->get_future()).get();
    futuresNum ++;
}


double Thread_pool::average()
{
    return futuresTotalScore / futuresNum;
};

void Thread_pool::stop(){

    {
        std::unique_lock<std::mutex> lock{mEventMutex};
        mStopping = true;
    }
 
    mEventVar.notify_all();

    for (auto &thread : mThreads)
        thread.join();

};

void Thread_pool::start(std::size_t numThreads)
{
    for (auto i = 0u; i < numThreads; ++i)
    {
        mThreads.emplace_back([=] 
        {
            bool continueExecution = true;
            while (continueExecution)
            {
                Task task;

                {
                    std::unique_lock<std::mutex> lock{mEventMutex};

                    mEventVar.wait(lock, [=] { return mStopping || !mTasks.empty(); });

                    if (mStopping && mTasks.empty())
                        continueExecution = false;
                    else{
                        task = std::move(mTasks.front());
                        mTasks.pop();
                    }
                
                }

                if(continueExecution)
                    task();
            }
        });
    }
};

void Thread_pool::get_var()
{
    std::cout << "futuresTotalScore: " << futuresTotalScore <<"\nfutureNum: " << futuresNum << '\n';
}

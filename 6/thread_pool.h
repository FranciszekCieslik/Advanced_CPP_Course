#include <functional>
#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <future>

class Thread_pool
{
public:
    using Task = std::function<void()>;

private:
    std::vector<std::thread> mThreads;
    std::mutex mEventMutex;
    std::queue<Task> mTasks;

    std::condition_variable mEventVar;
    bool mStopping{false};

    double futuresTotalScore{0};
    double futuresNum{0};

public:
    explicit Thread_pool(std::size_t numThreads);
    ~Thread_pool();

    void add_task(std::function<double()> task);

    double average();
    void stop();

    void get_var();
    
private:
    void start(std::size_t numThreads);
    
};




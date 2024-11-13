#include <vector>
#include <memory>
#include <chrono>
#include <mutex>
#include <thread>

class fuel_tank
{
private:
    unsigned int fuel;
    std::mutex mutex;

public:
    // inicjalizator
    fuel_tank() : fuel{0} {};
    fuel_tank(unsigned int n) : fuel{n} {};
    // destruktor
    ~fuel_tank(){};
    // konstruktor kopiujący
    fuel_tank(const fuel_tank &other) { fuel = other.fuel; };

    fuel_tank &operator=(const fuel_tank &other)
    {
        fuel = other.fuel;
        return *this;
    };

    fuel_tank(fuel_tank &&other) noexcept { fuel = other.fuel; };

    fuel_tank &operator=(fuel_tank &&other) noexcept
    {
        fuel = other.fuel;
        other.fuel = 0;
        return *this;
    };

    unsigned int getfuel(){return fuel;}

    unsigned int refuel(unsigned int n)
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (fuel >= n)
        {
            fuel -= n;
            printf("Fuel: %d\n", fuel);
            return n;
        }
        else
        {
            // unsigned int tmp = fuel;
            // fuel = 0;
            // return tmp;
            return 0u;
        }
    };
};

class engine
{
private:
    std::vector<std::shared_ptr<fuel_tank>> tanks;
    std::chrono::seconds interval;
    unsigned int fuelAmount;
    std::thread refuelThread;
    std::mutex mutex;

public:
    engine(std::chrono::seconds interval, unsigned int n)
        : interval(interval), fuelAmount(n)
    {
        refuelThread = std::thread(&engine::refuelThreadFunc, this);
    };
    ~engine()
    {
        if (refuelThread.joinable())
        {
            refuelThread.join();
        }
    };

private:
    void refuelThreadFunc();

public:
    void connectFuelTank(std::shared_ptr<fuel_tank> tank)
    {
        std::lock_guard<std::mutex> lock(mutex);
        tanks.push_back(tank);
    }
};

void engine::refuelThreadFunc()
{
    while (!tanks.empty())
    {
        std::lock_guard<std::mutex> lock(mutex);
        auto tank = tanks.back();
        if (0u == tank->refuel(fuelAmount))
        {
            tanks.pop_back();
        };
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    } 
};

#include <iostream>
#include "my_class.h"
#include "cpplab.h"

int main()
{
    std::vector<std::shared_ptr<fuel_tank>> fuelTanks;
    for (int i = 0; i < 5; ++i)
    {
        fuelTanks.push_back(std::make_shared<fuel_tank>(20));
    }

    engine eng1(std::chrono::seconds(2), 5);
    engine eng2(std::chrono::seconds(1), 1);
    engine eng3(std::chrono::seconds(3), 2);

    for (auto &tank : fuelTanks)
    {
        eng1.connectFuelTank(tank);
        eng2.connectFuelTank(tank);
        eng3.connectFuelTank(tank);
    }

    cpplab::non0_ptr<int> myNonNullPtr(new int(42));
    std::cout << "Value using non0_ptr: " << *myNonNullPtr.get() << std::endl;

    try
    {
        // Trying to create non0_ptr with nullptr (will throw exception)
        cpplab::non0_ptr<int> invalidPtr(nullptr); // This should now correctly generate an error
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
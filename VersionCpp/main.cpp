#include "hpp/driver.hpp"

#include <iostream>

using namespace logistics;

static void PrintSeparator(const char* title)
{
    std::cout << "\n===== " << title << " =====\n";
}

int main()
{

    constexpr std::size_t N = 3;

    PrintSeparator("Массив динамических объектов класса");

    Driver* drivers[N] = {
        new Driver{ 201, "Кузнецов К. К." },
        new Driver{ 202, "Смирнов С. С." },
        new Driver{ 203, "Волков В. В." },
    };

    for (std::size_t i = 0; i < N; ++i)
    {
        drivers[i]->Print();
    }
    for (std::size_t i = 0; i < N; ++i)
    {
        delete drivers[i];
    }

    std::cout << "\nПрограмма завершена\n";
    return 0;
}

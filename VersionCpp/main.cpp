#include "hpp/driver.hpp"
#include "hpp/cargo.hpp"

#include <iostream>

using namespace logistics;

static void PrintSeparator(const char* title)
{
    std::cout << "\n===== " << title << " =====\n";
}

int main()
{

    constexpr std::size_t N = 3;


    PrintSeparator("Статическая инициализация Cargo");

    {
        Cargo cargo1{ 1500.0, "Барнаул" };
        cargo1.Print();

        Cargo cargo2{ 800.0, "Бийск" };
        cargo2.Print();

        std::cout << "\n-- проверка правила: отрицательный вес --\n";
        cargo2.SetWeightKg(-10.0);
        cargo2.Print();

        std::cout << "\n-- корректное изменение веса --\n";
        cargo2.SetWeightKg(950.0);
        cargo2.Print();
    }


    PrintSeparator("Динамическая инициализация Cargo (new/delete)");

    Cargo* cargo3 = new Cargo{ 2000.0, "Новосибирск" };
    cargo3->Print();

    std::cout << "\n-- работа по указателю --\n";
    cargo3->SetWeightKg(2100.0);
    cargo3->Print();

    std::cout << "\n-- работа по ссылке --\n";
    Cargo& cargoRef = *cargo3;
    cargoRef.SetWeightKg(2200.0);
    cargoRef.Print();

    delete cargo3;


    PrintSeparator("Массив объектов класса Cargo");

    Cargo cargos[N] = {
        Cargo{ 100.0, "Томск" },
        Cargo{ 200.0, "Омск" },
        Cargo{ 300.0, "Кемерово" },
    };

    for (std::size_t i = 0; i < N; ++i)
    {
        cargos[i].Print();
    }


    PrintSeparator("Массив динамических объектов класса Driver");

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


    PrintSeparator("Массив динамических объектов класса Cargo");

    Cargo* cargosDyn[N] = {
        new Cargo{ 10.0, "Горно-Алтайск" },
        new Cargo{ 20.0, "Рубцовск" },
        new Cargo{ 30.0, "Славгород" },
    };

    for (std::size_t i = 0; i < N; ++i)
    {
        cargosDyn[i]->Print();
    }
    for (std::size_t i = 0; i < N; ++i)
    {
        delete cargosDyn[i];
    }

    std::cout << "\nПрограмма завершена\n";
}

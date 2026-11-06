#include "hpp/truck.hpp"
#include "hpp/van.hpp"

#include <iostream>
#include <memory>
#include <string>


using namespace logistics;

int main() {
    constexpr int N = 4;

    std::cout << "==================== 1. Создание объектов ====================\n";
    auto truck1 = std::make_unique<Truck>("А111АА", 10.0, 4, 2022);
    auto truck2 = std::make_unique<Truck>("Б222ББ", 7.0, 2, 2020);

    auto van1 = std::make_unique<Van>("В333ВВ", 3.0, 2023, 12.5);
    auto van2 = std::make_unique<Van>("Г444ГГ", 1.5, 2010, 8.0);

    truck1->SetState(BaseVehicle::State::eInRepair);

    std::cout << "\n==================== 2. Массив базовых классов ====================\n";
    std::unique_ptr<BaseVehicle> fleet[N];
    fleet[0] = std::move(truck1);
    fleet[1] = std::move(truck2);
    fleet[2] = std::move(van1);
    fleet[3] = std::move(van2);

    for (int i = 0; i < N; ++i) {
        std::cout << "--- " << fleet[i]->GetType() << " ---\n";
        std::string desc = fleet[i]->Describe();
        std::cout << desc << "\n";

        std::cout << "  [Анализ строки] ";
        size_t pos = desc.find("Госномер: ");
        if (pos != std::string::npos) {
            std::string plate = desc.substr(pos + 18, 9);
            std::cout << "найден номер: '" << plate << "'\n";
        }
        else {
            std::cout << "номер не найден\n";
        }

        std::cout << "Результат ТО: " << (fleet[i]->PassInspection() ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН") << "\n\n";
    }

    std::cout << "==================== 3. Клонирование ====================\n";
    std::unique_ptr<BaseVehicle> clonedVan = fleet[2]->Clone();
    std::cout << "Оригинал: " << fleet[2]->Describe() << "\n";
    std::cout << "Клон:     " << clonedVan->Describe() << "\n\n";

    std::cout << "==================== 4. Поверхностное и глубокое копирование ====================\n";

    std::cout << "1. ГЛУБОКОЕ КОПИРОВАНИЕ:\n";
    auto originalTruck = std::make_unique<Truck>("Т777ТТ", 8.0, 3, 2021);
    originalTruck->SetDocs("Лист №1");

    Truck deepCopy = *originalTruck;

    std::cout << "Оригинал: " << originalTruck->GetDocs() << "\n";
    std::cout << "Копия: " << deepCopy.GetDocs() << "\n";

    deepCopy.SetDocs("Лист №2");

    std::cout << "После изменения копии:\n";
    std::cout << "Оригинал: " << originalTruck->GetDocs() << "\n";
    std::cout << "Копия: " << deepCopy.GetDocs() << "\n\n";

    std::cout << "2. ПОВЕРХНОСТНОЕ КОПИРОВАНИЕ:\n";
    auto sharedTruck = std::make_shared<Truck>("П888ПП", 5.0, 2, 2020);
    sharedTruck->SetDocs("Лист №3");

    std::shared_ptr<Truck> shallowCopy = sharedTruck;

    std::cout << "Оригинал: " << sharedTruck->GetDocs() << "\n";
    std::cout << "Копия: " << shallowCopy->GetDocs() << "\n";

    shallowCopy->SetDocs("Лист №4");

    std::cout << "После изменения копии:\n";
    std::cout << "Оригинал: " << sharedTruck->GetDocs() << "\n";
    std::cout << "Копия: " << shallowCopy->GetDocs() << "\n\n";

    std::cout << "==================== 5. Очистка ====================\n";
    for (int i = 0; i < N; ++i) {
        fleet[i].reset();
    }
    clonedVan.reset();
    originalTruck.reset();
    sharedTruck.reset();

    return 0;
}

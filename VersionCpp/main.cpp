#include "hpp/cargo.hpp"
#include "hpp/driver.hpp"
#include "hpp/order.hpp"

#include <iostream>
#include <memory>

using namespace logistics;

int main() {
    std::cout << "========= 1. Композиция: Order владеет Cargo =========\n";
    {
        Order order{ 1, true, 1500.0, "Барнаул" };
        order.Print();

        std::cout << "  Вес груза через заказ: "
            << order.GetCargo().GetWeightKg() << " кг\n";
    } 

    std::cout << "\n========= 2. Агрегация: weak_ptr на внешний Driver =========\n";
    auto sharedDriver = std::make_shared<Driver>(101, "Иванов И. И.");

    {
        Order order{ 2, true, 800.0, "Бийск" };
        order.AssignDriver(sharedDriver);
        order.StartTransit();
        order.Deliver();
    }

    std::cout << "\n--- После уничтожения Order водитель жив: ---\n";
    sharedDriver->Print();


    std::cout << "\n========= 3. Проверка правила =========\n";
    auto restingDriver = std::make_shared<Driver>(102, "Петров П. П.");
    restingDriver->GoToRest();

    Order order3{ 3, false, 500.0, "Омск" };
    order3.AssignDriver(restingDriver);  
    order3.Print();

    std::cout << "\n========= 4. unique_ptr: уничтожение и передача владения =========\n";
    {
        auto heapOrder = std::make_unique<Order>(4, true, 200.0, "Томск");
        heapOrder->Print();

        std::unique_ptr<Order> movedOrder = std::move(heapOrder);
        if (!heapOrder)
        {
            std::cout << "  heapOrder пуст после std::move\n";
        }
        movedOrder->Print();
    }

    std::cout << "\n========= 5. shared_ptr: use_count() растёт и уменьшается =========\n";
    auto first = std::make_shared<Driver>(201, "Сидоров С. С.");
    std::cout << "количество активных shared_ptr владеющих объектом: " << first.use_count() << "\n";

    {
        auto second = first;
        std::cout << "  количество активных shared_ptr владеющих объектом после копирования: " 
                << first.use_count() << "\n";
    }

    std::cout << "  количество активных shared_ptr владеющих объектом после выхода из блока: " 
            << first.use_count() << "\n";

    first.reset();


    std::cout << "\n========= 6. weak_ptr: до и после уничтожения =========\n";
    std::weak_ptr<Driver> weak;
    std::shared_ptr<Driver> owner;
    
    {
        owner = std::make_shared<Driver>(301, "Долгоживущий Д. Д.");
        weak = owner;

        if (auto alive = weak.lock())
        {
            alive->Print();
        }
    }

    owner.reset();

    if (auto alive = weak.lock())
    {
        std::cout << "не должно выполниться объект ещё жив\n";
    }
    else
    {
        std::cout << "объект уничтожен, weak.lock() вернул пустой указатель\n";
    }
    
    std::cout << "\n========= 7. массив объектов и массив умных указателей =========\n";
    {
        Cargo cargos[2] = { Cargo{ 10.0, "А" }, Cargo{ 20.0, "Б" } };
        for (const auto& c : cargos) c.Print();
    }

    {
        std::unique_ptr<Driver> drivers[2];
        drivers[0] = std::make_unique<Driver>(201, "А. А.");
        drivers[1] = std::make_unique<Driver>(202, "Б. Б.");

        for (const auto& d : drivers) d->Print();
    }

    return 0;
}
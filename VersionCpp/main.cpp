#include "hpp/truck.hpp"
#include "hpp/van.hpp"
#include "hpp/repairvehicle.hpp"
#include "hpp/cargopolicy.hpp"
#include "hpp/driver.hpp"
#include "hpp/order.hpp"
#include "hpp/iassignable.hpp"
#include "hpp/exceptions.hpp"

#include <iostream>
#include <memory>
#include <string>


using namespace logistics;

int main() {
    std::cout << "\n================== 1. Раннее и позднее связывание ==================\n";
    std::unique_ptr<BaseVehicle> v = std::make_unique<Truck>("A123BC", 10.0, 4, 2020, std::make_unique<StandardCargoPolicy>());
    std::cout << "GetKind()  (невирт., раннее): " << v->GetKind() << "\n";
    std::cout << "Describe() (вирт., позднее):  " << v->Describe() << "\n";

    std::cout << "\n================== 2. Проверка типа во время выполнения ==================\n";
    std::unique_ptr<BaseVehicle> fleet[3] = {
        std::make_unique<Truck>("B456CD", 8.0, 3, 2021, std::make_unique<StandardCargoPolicy>()),
        std::make_unique<Van>("D222BB", 3.0, 2023, 12.0),
        std::make_unique<RepairVehicle>("R001RP", 5.0, 2010)
    };

    Cargo cargo{ 2000.0, "Тверь" };
    for (auto& f : fleet)
    {
        if (auto* a = dynamic_cast<IAssignable*>(f.get()))
        {
            if (!TryAssign(*a, cargo, 42))
            {
                std::cout << f->GetType() << " не подходит по грузоподъёмности\n";
            }
        }
        else
        {
            std::cout << f->GetType() << " нельзя назначить на рейс\n";
        }
    }

    std::cout << "\n================== 3. Конфигурирование ==================\n";
    auto t = std::make_unique<Truck>("E333EE", 5.0, 3, 2021, std::make_unique<StandardCargoPolicy>());
    Order heavy{ 12, true, 5500.0, "Сочи" };

    std::cout << "обычное правило: CanTake = " << t->CanTake(heavy.GetCargo()) << "\n";
    t->SetPolicy(std::make_unique<UrgentCargoPolicy>());
    std::cout << "срочное правило: CanTake = " << t->CanTake(heavy.GetCargo()) << "\n";

    std::cout << "\n========= 4. Исключения (успешное действие) =========\n";
    auto driver = std::make_shared<Driver>(1, "Иванов");
    try
    {
        heavy.AssignDriver(driver);
        heavy.StartTransit();
        heavy.Deliver();
        std::cout << "заказ 12 успешно доставлен\n";
    }
    catch (const DriverUnavailable& e) { std::cout << "водитель: " << e.what() << "\n"; }
    catch (const InvalidOrderState& e) { std::cout << "состояние: " << e.what() << "\n"; }
    catch (const std::exception& e) { std::cout << "ошибка: " << e.what() << "\n"; }

    std::cout << "\n================== 5. Исключения (нарушение правил) ==================\n";

    try
    {
        heavy.Deliver();
    }
    catch (const InvalidOrderState& e) { std::cout << "перехвачено: " << e.what() << "\n"; }
    catch (const std::exception& e) { std::cout << "ошибка: " << e.what() << "\n"; }

    auto t1 = std::make_unique<Truck>("G555GG", 5.0, 3, 2026, std::make_unique<StandardCargoPolicy>());
    try
    {
        if (!t1->CanTake(heavy.GetCargo()))
        {
            throw OverloadError{ heavy.GetCargo().GetWeightKg(), t1->GetCapacity() };
        }
    }
    catch (const OverloadError& e) { std::cout << "перехвачено: " << e.what() << "\n"; }
    catch (const std::exception& e) { std::cout << "ошибка: " << e.what() << "\n"; }

    try
    {
        Cargo bad{ 100.0, "Омск" };
        bad.SetWeightKg(-5.0);
    }
    catch (const NegativeWeight& e) { std::cout << "перехвачено: " << e.what() << "\n"; }
    catch (const std::exception& e) { std::cout << "ошибка: " << e.what() << "\n"; }

    try
    {
        auto resting = std::make_shared<Driver>(2, "Петров");
        resting->SetState(Driver::State::eOnTrip);
        resting->GoToRest();
    }
    catch (const DriverUnavailable& e) { std::cout << "перехвачено: " << e.what() << "\n"; }
    catch (const std::exception& e) { std::cout << "ошибка: " << e.what() << "\n"; }

    try
    {
        auto* busy = dynamic_cast<IAssignable*>(fleet[0].get());
        if (busy != nullptr && !busy->IsAvailable())
        {
            throw NoAvailableVehicle{ cargo.GetDestination() };
        }
    }
    catch (const NoAvailableVehicle& e) { std::cout << "перехвачено: " << e.what() << "\n"; }
    catch (const std::exception& e) { std::cout << "ошибка: " << e.what() << "\n"; }

    return 0;
}

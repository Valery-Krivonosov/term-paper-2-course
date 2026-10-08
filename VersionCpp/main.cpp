#include "hpp/cargo.hpp"
#include "hpp/driver.hpp"
#include "hpp/order.hpp"

#include <iostream>

using namespace logistics;

int main() {
    std::cout << "========= 1. Композиция: Order владеет Cargo =========\n";
    {
        Cargo cargo{ 1500.0, "Барнаул" };
        Order order{ 1, true, cargo }; 
        order.Print();

        std::cout << "  Вес груза через заказ: "
                << order.GetCargo().GetWeightKg() << " кг\n";
    } 

    std::cout << "\n========= 2. Агрегация: Order использует внешний Driver =========\n";
    Driver* sharedDriver = new Driver{ 101, "Иванов И. И." };

    {
        Order order{ 2, true, Cargo{ 800.0, "Бийск" } };
        order.AssignDriver(*sharedDriver); 
        order.StartTransit();
        order.Deliver();
    }

    std::cout << "\n--- После уничтожения Order водитель жив: ---\n";
    sharedDriver->Print();  

    delete sharedDriver;    

    std::cout << "\n========= 3. Проверка правила =========\n";
    Driver resting{ 102, "Петров П. П." };
    resting.GoToRest();

    Order order3{ 3, false, Cargo{ 500.0, "Омск" } };
    order3.AssignDriver(resting); 
    order3.Print();

    std::cout << "\n========= 4. Стек, указатель, ссылка, new/delete =========\n";
    Order stackOrder{ 4, false, Cargo{ 100.0, "Томск" } };  
    Order* heapOrder = new Order{ 5, true, Cargo{ 200.0, "Омск" } }; 
    stackOrder.Print();           
    heapOrder->Print();           
    Order& ref = *heapOrder;      
    ref.Print();

    delete heapOrder;

    std::cout << "\n========= 5. Массив объектов и массив динамических объектов =========\n";
    Cargo cargos[2] = { Cargo{ 10.0, "А" }, Cargo{ 20.0, "Б" } };
    for (auto& c : cargos) c.Print();

    Driver** driverPtrArray = new Driver * [2];
    driverPtrArray[0] = new Driver{ 201, "А. А." };
    driverPtrArray[1] = new Driver{ 202, "Б. Б." };
    for (int i = 0; i < 2; ++i) delete driverPtrArray[i];
    delete[] driverPtrArray;

    return 0;
}
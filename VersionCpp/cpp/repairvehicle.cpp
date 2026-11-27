#include "../hpp/repairvehicle.hpp"

#include <iostream>


namespace logistics
{
    RepairVehicle::RepairVehicle(std::string_view plateNumber, double capacity, int year)
        : BaseVehicle{ plateNumber, capacity, year }
    {
        SetState(State::eInRepair);
        std::cout << "[RepairVehicle] constructor: id=" << GetId() << "\n";
    }

    RepairVehicle::~RepairVehicle()
    {
        std::cout << "[RepairVehicle] destructor: id=" << GetId() << "\n";
    }

    std::string RepairVehicle::GetType() const
    {
        return "Ремонтная единица";
    }

    bool RepairVehicle::PassInspection() const
    {
        return false;
    }

    std::string RepairVehicle::Describe() const
    {
        return "Ремонтная единица, Госномер: " + GetPlateNumber() + " (на рейс не назначается)";
    }

    std::unique_ptr<BaseVehicle> RepairVehicle::Clone() const
    {
        return std::make_unique<RepairVehicle>(*this);
    }
}

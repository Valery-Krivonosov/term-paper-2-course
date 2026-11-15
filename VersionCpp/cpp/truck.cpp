#include "../hpp/truck.hpp"

#include <iostream>


namespace logistics
{
    Truck::Truck(std::string_view plateNumber, double capacity, int axles, int year)
        : BaseVehicle{ plateNumber, capacity, year }
        , m_axles{ axles }
    {
        std::cout << "[Truck] constructor: " << GetType() << " id=" << GetId() << "\n";
    }

    Truck::Truck(const Truck& other)
        : BaseVehicle{ other }
        , m_axles{ other.m_axles }
    {
        std::cout << "[Truck] copy constructor: id=" << GetId() << "\n";
    }

    Truck& Truck::operator=(const Truck& other)
    {
        if (this != &other)
        {
            BaseVehicle::operator=(other);
            m_axles = other.m_axles;
        }
        return *this;
    }

    Truck::Truck(Truck&& other) noexcept
        : BaseVehicle{ std::move(other) }
        , m_axles{ other.m_axles }
    {
        other.m_axles = 0;
        std::cout << "[Truck] move constructor: id=" << GetId() << "\n";
    }

    Truck& Truck::operator=(Truck&& other) noexcept
    {
        if (this != &other)
        {
            BaseVehicle::operator=(std::move(other));
            m_axles = other.m_axles;
            other.m_axles = 0;
        }
        return *this;
    }

    Truck::~Truck()
    {
        std::cout << "[Truck] destructor: id=" << GetId() << "\n";
    }

    std::string Truck::GetType() const
    {
        return "Грузовик";
    }

    bool Truck::PassInspection() const
    {
        if (GetState() == State::eInRepair)
        {
            return false;
        }

        return (m_year >= 2015) && (m_axles >= 3);
    }

    std::string Truck::Describe() const
    {
        return BaseVehicle::Describe() + ", Осей: " + std::to_string(m_axles);
    }

    std::unique_ptr<BaseVehicle> Truck::Clone() const
    {
        return std::make_unique<Truck>(*this);
    }
}

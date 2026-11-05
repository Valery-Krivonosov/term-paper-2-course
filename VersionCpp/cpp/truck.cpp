#include "../hpp/truck.hpp"

#include <iostream>


namespace logistics
{
    Truck::Truck(std::string_view plateNumber, double capacity, int axles, int year)
        : BaseVehicle{ plateNumber, capacity }
        , m_axles{ axles }
        , m_year{ year }
    {
        std::cout << "[Truck] constructor: " << GetType() << " id=" << GetId() << "\n";
    }

    Truck::Truck(const Truck& other)
        : BaseVehicle{ other }
        , m_axles{ other.m_axles }
        , m_year{ other.m_year }
    {
        std::cout << "[Truck] copy constructor: id=" << GetId() << "\n";
    }

    Truck& Truck::operator=(const Truck& other)
    {
        if (this != &other)
        {
            BaseVehicle::operator=(other);
            m_axles = other.m_axles;
            m_year = other.m_year;
        }
        return *this;
    }

    Truck::Truck(Truck&& other) noexcept
        : BaseVehicle{ std::move(other) }
        , m_axles{ other.m_axles }
        , m_year{ other.m_year }
    {
        other.m_axles = 0;
        other.m_year = 0;
        std::cout << "[Truck] move constructor: id=" << GetId() << "\n";
    }

    Truck& Truck::operator=(Truck&& other) noexcept
    {
        if (this != &other)
        {
            BaseVehicle::operator=(std::move(other));
            m_axles = other.m_axles;
            m_year = other.m_year;
            other.m_axles = 0;
            other.m_year = 0;
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

        bool yearOk = (m_year >= 2015);
        bool axlesOk = (m_axles >= 3);

        return yearOk && axlesOk;
    }

    std::string Truck::Describe() const
    {
        return BaseVehicle::Describe() +
            ", Осей: " + std::to_string(m_axles) +
            ", Год: " + std::to_string(m_year);
    }

    std::unique_ptr<BaseVehicle> Truck::Clone() const
    {
        return std::make_unique<Truck>(*this);
    }
}

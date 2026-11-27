#include "../hpp/truck.hpp"
#include "../hpp/cargopolicy.hpp"
#include "../hpp/exceptions.hpp"

#include <iostream>


namespace logistics
{
    Truck::Truck(std::string_view plateNumber, double capacity, int axles, int year,
        std::unique_ptr<ICargoPolicy> policy)
        : BaseVehicle{ plateNumber, capacity, year }
        , m_axles{ axles }
        , m_policy{ std::move(policy) }
    {
        std::cout << "[Truck] constructor: " << GetType() << " id=" << GetId() << "\n";
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
        return std::make_unique<Truck>(GetPlateNumber(), GetCapacity(), m_axles, GetYear(),
            std::make_unique<StandardCargoPolicy>());
    }

    bool Truck::CanTake(const Cargo& cargo) const
    {
        return GetState() == State::eAvailable
            && m_policy != nullptr
            && m_policy->Accepts(cargo, GetCapacity());
    }

    void Truck::AssignTo(std::uint64_t orderId)
    {
        if (GetState() != State::eAvailable)
        {
            throw NoAvailableVehicle{ "грузовик id=" + std::to_string(GetId()) + " занят" };
        }
        SetState(State::eOnTrip);
        std::cout << "[Truck] id=" << GetId() << " назначен на заказ id=" << orderId << "\n";
    }

    void Truck::CompleteTrip() noexcept
    {
        SetState(State::eAvailable);
    }

    bool Truck::IsAvailable() const
    {
        return GetState() == State::eAvailable;
    }

    void Truck::SetPolicy(std::unique_ptr<ICargoPolicy> policy)
    {
        m_policy = std::move(policy);
        std::cout << "[Truck] правило допуска груза изменено\n";
    }
}

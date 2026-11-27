#include "../hpp/van.hpp"
#include "../hpp/cargo.hpp"
#include "../hpp/exceptions.hpp"

#include <iostream>


namespace logistics
{
    Van::Van(std::string_view plateNumber, double capacity, int year, double volume)
        : BaseVehicle{ plateNumber, capacity, year }
        , m_volume{ volume }
    {
        std::cout << "[Van] constructor: " << GetType() << " id=" << GetId() << "\n";
    }

    Van::Van(const Van& other)
        : BaseVehicle{ other }
        , m_volume{ other.m_volume }
    {
        std::cout << "[Van] copy constructor: id=" << GetId() << "\n";
    }

    Van& Van::operator=(const Van& other)
    {
        if (this != &other)
        {
            BaseVehicle::operator=(other);
            m_volume = other.m_volume;
        }
        return *this;
    }

    Van::Van(Van&& other) noexcept
        : BaseVehicle{ std::move(other) }
        , m_volume{ other.m_volume }
    {
        other.m_volume = 0.0;
        std::cout << "[Van] move constructor: id=" << GetId() << "\n";
    }

    Van& Van::operator=(Van&& other) noexcept
    {
        if (this != &other)
        {
            BaseVehicle::operator=(std::move(other));
            m_volume = other.m_volume;
            other.m_volume = 0.0;
        }
        return *this;
    }

    Van::~Van()
    {
        std::cout << "[Van] destructor: id=" << GetId() << "\n";
    }

    std::string Van::GetType() const
    {
        return "Фургон";
    }

    bool Van::PassInspection() const
    {
        if (GetState() == State::eInRepair)
        {
            return false;
        }

        return (m_year >= 2015) && (m_year >= 2015);
    }

    std::string Van::Describe() const
    {
        return "Фургон, Госномер: " + GetPlateNumber() +
            ", Тоннаж: " + std::to_string(GetCapacity()) + "т, " +
            "Год: " + std::to_string(m_year) + ", " +
            "Объем: " + std::to_string(m_volume) + " кубических метров, " +
            "Состояние: " + (GetState() == State::eInRepair ? "В ремонте" : "Готов к работе");
    }

    std::unique_ptr<BaseVehicle> Van::Clone() const
    {
        return std::make_unique<Van>(*this);
    }


    bool Van::CanTake(const Cargo& cargo) const
    {
        return GetState() == State::eAvailable && cargo.GetWeightKg() <= GetCapacity() * 1000.0;
    }

    void Van::AssignTo(std::uint64_t orderId)
    {
        if (GetState() != State::eAvailable)
        {
            throw NoAvailableVehicle{ "фургон id=" + std::to_string(GetId()) + " занят" };
        }
        SetState(State::eOnTrip);
        std::cout << "[Van] id=" << GetId() << " назначен на заказ id=" << orderId << "\n";
    }

    void Van::CompleteTrip() noexcept
    {
        SetState(State::eAvailable);
    }

    bool Van::IsAvailable() const
    {
        return GetState() == State::eAvailable;
    }
}

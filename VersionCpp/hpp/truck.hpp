#pragma once

#include "basevehicle.hpp"


namespace logistics
{
    class Truck : public BaseVehicle
    {
    private:
        int m_axles{ 0 };
        int m_year{ 2020 };

    public:
        Truck(std::string_view plateNumber, double capacity, int axles, int year);

        Truck(const Truck& other);
        Truck& operator=(const Truck& other);
        Truck(Truck&& other) noexcept;
        Truck& operator=(Truck&& other) noexcept;

        ~Truck() override;

        [[nodiscard]] std::string GetType() const override;

        [[nodiscard]] bool PassInspection() const override;

        [[nodiscard]] std::string Describe() const override;

        [[nodiscard]] std::unique_ptr<BaseVehicle> Clone() const override;
    };
}

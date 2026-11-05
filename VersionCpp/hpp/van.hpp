#pragma once

#include "basevehicle.hpp"


namespace logistics
{
    class Van final : public BaseVehicle
    {
    private:
        int m_year{ 2020 };
        double m_volume{ 0.0 };

    public:
        Van(std::string_view plateNumber, double capacity, int year, double volume);

        Van(const Van& other);
        Van& operator=(const Van& other);
        Van(Van&& other) noexcept;
        Van& operator=(Van&& other) noexcept;

        ~Van() override;

        [[nodiscard]] std::string GetType() const override;

        [[nodiscard]] bool PassInspection() const override;

        [[nodiscard]] std::string Describe() const override;

        [[nodiscard]] std::unique_ptr<BaseVehicle> Clone() const override;
    };
}

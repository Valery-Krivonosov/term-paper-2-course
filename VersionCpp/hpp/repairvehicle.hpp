#pragma once

#include "basevehicle.hpp"


namespace logistics
{
    class RepairVehicle final : public BaseVehicle
    {
    public:
        RepairVehicle(std::string_view plateNumber, double capacity, int year);
        ~RepairVehicle() override;

        [[nodiscard]] std::string GetType() const override;
        [[nodiscard]] bool PassInspection() const override;
        [[nodiscard]] std::string Describe() const override;
        [[nodiscard]] std::unique_ptr<BaseVehicle> Clone() const override;

        [[nodiscard]] std::string GetKind() const
        {
            return "ремонтная единица";
        }
    };
}

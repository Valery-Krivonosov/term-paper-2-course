#pragma once

#include "basevehicle.hpp"
#include "iassignable.hpp"
#include "cargopolicy.hpp"


namespace logistics
{
    class Truck : public BaseVehicle, public IAssignable
    {
    private:
        int m_axles{ 0 };
        std::unique_ptr<ICargoPolicy> m_policy{};

    public:
        Truck(std::string_view plateNumber, double capacity, int axles, int year,
                std::unique_ptr<ICargoPolicy> policy);

        Truck(const Truck&)                 = delete;
        Truck& operator=(const Truck&)      = delete;
        Truck(Truck&& other) noexcept;
        Truck& operator=(Truck&& other) noexcept;

        ~Truck() override;

        [[nodiscard]] std::string GetType() const override;

        [[nodiscard]] bool PassInspection() const override;

        [[nodiscard]] std::string Describe() const override;

        [[nodiscard]] std::unique_ptr<BaseVehicle> Clone() const override;

        [[nodiscard]] std::string GetKind() const
        {
            return "грузовик";
        }


        void SetPolicy(std::unique_ptr<ICargoPolicy> policy);

        [[nodiscard]] bool CanTake(const Cargo& cargo) const override;

        void AssignTo(std::uint64_t orderId) override;
        
        void CompleteTrip() noexcept override;
        
        [[nodiscard]] bool IsAvailable() const override;
    };
}

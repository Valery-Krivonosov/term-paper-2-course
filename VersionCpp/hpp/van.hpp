#pragma once

#include "basevehicle.hpp"
#include "iassignable.hpp"


namespace logistics
{
    class Van final : public BaseVehicle, public IAssignable
    {
    private:
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
    
        
        [[nodiscard]] std::string GetKind() const
        {
            return "фургон";
        }

        [[nodiscard]] bool CanTake(const Cargo& cargo) const override;

        void AssignTo(std::uint64_t orderId) override;

        void CompleteTrip() noexcept override;

        [[nodiscard]] bool IsAvailable() const override;
    };
}

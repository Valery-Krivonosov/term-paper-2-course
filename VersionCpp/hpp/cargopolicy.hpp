#pragma once


namespace logistics
{
    class Cargo;

    class ICargoPolicy
    {
    public:
        virtual ~ICargoPolicy() = default;
        virtual bool Accepts(const Cargo& cargo, double capacityTons) const = 0;
    };

    class StandardCargoPolicy : public ICargoPolicy
    {
    public:
        bool Accepts(const Cargo& cargo, double capacityTons) const override;
    };

    class UrgentCargoPolicy : public ICargoPolicy
    {
    public:
        bool Accepts(const Cargo& cargo, double capacityTons) const override;
    };
}

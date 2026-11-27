#pragma once

#include <cstdint>

namespace logistics
{
    class Cargo;

    class IAssignable
    {
    public:
        virtual ~IAssignable() = default;

        virtual bool CanTake(const Cargo& cargo) const = 0;
        virtual void AssignTo(std::uint64_t orderId) = 0;
        virtual void CompleteTrip() noexcept = 0;
        virtual bool IsAvailable() const = 0;
    };

    inline bool TryAssign(IAssignable& item, const Cargo& cargo, std::uint64_t orderId)
    {
        if (!item.IsAvailable())
        {
            return false;
        }
        if (!item.CanTake(cargo))
        {
            return false;
        }
        item.AssignTo(orderId);
        return true;
    }

}

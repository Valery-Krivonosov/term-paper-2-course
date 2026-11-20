#include "../hpp/cargopolicy.hpp"
#include "../hpp/cargo.hpp"

namespace logistics
{
    bool StandardCargoPolicy::Accepts(const Cargo& cargo, double capacityTons) const
    {
        return cargo.GetWeightKg() <= capacityTons * 1000.0;
    }

    bool UrgentCargoPolicy::Accepts(const Cargo& cargo, double capacityTons) const
    {
        return cargo.GetWeightKg() <= capacityTons * 1000.0 * 1.10;
    }
}

#pragma once

#include <stdexcept>
#include <string>
#include <string_view>


namespace logistics
{
    class NoAvailableVehicle : public std::runtime_error
    {
    public:
        explicit NoAvailableVehicle(std::string_view destination)
            : std::runtime_error("нет свободного транспорта для пункта " + std::string(destination))
        {
        }
    };

    class OverloadError : public std::runtime_error
    {
    public:
        OverloadError(double weightKg, double capacityTons)
            : std::runtime_error("вес груза " + std::to_string(weightKg) +
                " кг превышает грузоподъёмность " + std::to_string(capacityTons) + " т")
        {
        }
    };

    class DriverUnavailable : public std::runtime_error
    {
    public:
        explicit DriverUnavailable(std::string_view name)
            : std::runtime_error("водитель " + std::string(name) + " недоступен")
        {
        }
    };

    class InvalidOrderState : public std::logic_error
    {
    public:
        explicit InvalidOrderState(std::string_view what)
            : std::logic_error(std::string(what))
        {
        }
    };

    class NegativeWeight : public std::logic_error
    {
    public:
        explicit NegativeWeight(double weightKg)
            : std::logic_error("вес не может быть отрицательным: " + std::to_string(weightKg))
        {
        }
    };
}

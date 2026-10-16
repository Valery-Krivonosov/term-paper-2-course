#include "../hpp/cargo.hpp"

#include <iostream>


namespace logistics
{
	Cargo::Cargo(double weightKg, std::string_view destination)
		: m_destination{ destination }
		, m_weightKg{ weightKg }
	{}
	
	Cargo::~Cargo() 
	{
		std::cout << "[Cargo] destructor: груз '" << m_destination
				  << "' (" << m_weightKg << " кг) уничтожен\n";
	}

	void Cargo::Print() const
	{
		std::cout << "  Груз: вес = " << m_weightKg
				  << " кг, пункт назначения = '" << m_destination << "'\n";
	}

	void Cargo::SetWeightKg(double weightKg)
	{
		if (weightKg < 0.0)
		{
			std::cout << "[Cargo] ошибка: вес не может быть отрицательным\n";
			return;
		}
		m_weightKg = weightKg;
	}

}

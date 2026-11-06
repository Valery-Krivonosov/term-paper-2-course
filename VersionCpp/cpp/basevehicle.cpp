#include "../hpp/basevehicle.hpp"

#include <iostream>


namespace logistics
{
	std::uint64_t BaseVehicle::s_lightCounter = 1000;
	std::uint64_t BaseVehicle::s_heavyCounter = 5000;

	std::uint64_t BaseVehicle::GenerateId(double capacity)
	{
		if (capacity > 5.0)
		{
			return ++s_heavyCounter;
		}
		return ++s_lightCounter;
	}

	BaseVehicle::BaseVehicle(std::string_view plateNumber, double capacity, int year)
		: m_plateNumber{ plateNumber }
		, m_capacity{ capacity }
		, m_year{ year }
		, m_id{ GenerateId(m_capacity) }
		, m_docs{ std::make_shared<std::string>("Пусто") }
	{
		std::cout << "[BaseVehicle] constructor: id=" << m_id << "\n";
	}

	BaseVehicle::BaseVehicle(const BaseVehicle& other)
		: m_state{ other.m_state }
		, m_plateNumber{ other.m_plateNumber }
		, m_capacity{ other.m_capacity }
		, m_year{ other.m_year }
		, m_id{ other.m_id }
		, m_docs{ std::make_shared<std::string>(*other.m_docs)}
	{
		std::cout << "[BaseVehicle] copy constructor: id=" << m_id << "\n";
	}

	BaseVehicle& BaseVehicle::operator=(const BaseVehicle& other)
	{
		if (this != &other)
		{
			m_state = other.m_state;
			m_plateNumber = other.m_plateNumber;
			m_capacity = other.m_capacity;
			m_year = other.m_year;
			m_id = other.m_id;
			m_docs = std::make_shared<std::string>(*other.m_docs);
		}
		return *this;
	}

	BaseVehicle::BaseVehicle(BaseVehicle&& other) noexcept
		: m_state{other.m_state }
		, m_plateNumber{ std::move(other.m_plateNumber) }
		, m_capacity{ other.m_capacity }
		, m_year{ other.m_year }
		, m_id{ other.m_id }
		, m_docs{ std::move(other.m_docs) }
	{
		other.m_id = 0;
		std::cout << "[BaseVehicle] move constructor: id=" << m_id << "\n";
	}

	BaseVehicle& BaseVehicle::operator=(BaseVehicle&& other) noexcept
	{
		if (this != &other)
		{
			m_state = other.m_state;
			m_plateNumber = std::move(other.m_plateNumber);
			m_capacity = other.m_capacity;
			m_year = other.m_year;
			m_id = other.m_id;
			m_docs = std::move(other.m_docs);
			other.m_id = 0;
		}
		return *this;
	}

	BaseVehicle::~BaseVehicle()
	{
		std::cout << "[BaseVehicle] destructor: id=" << m_id << "\n";
	}

	std::string BaseVehicle::Header() const
	{
		std::string stateStr;
		switch (m_state)
		{
			case State::eAvailable: stateStr = "Свободен"; 
				break;
			case State::eOnTrip: stateStr = "В рейсе";
				break;
			case State::eInRepair: stateStr = "В ремонте";
				break;
		}

		return "ID: " + std::to_string(m_id) +
			", Госномер: " + m_plateNumber +
			", Тоннаж: " + std::to_string(m_capacity) + "т" +
			", Год: " + std::to_string(m_year) +
			", Состояние: " +  stateStr;
	}

	std::string BaseVehicle::Describe() const
	{
		return Header();
	}
}

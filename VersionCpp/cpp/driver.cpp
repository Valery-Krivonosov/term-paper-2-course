#include "../hpp/driver.hpp"

#include <iostream>

namespace logistics
{
	Driver::Driver(std::uint64_t id, std::string_view fullName) 
	: m_id{ id }
	, m_fullName{ fullName } 	
	{}

	Driver::~Driver() 
	{
		std::cout << "[Driver] destructor: водитель (id=" << m_id << " , name=" << m_fullName << ") уничтожен\n";
	}

	std::string_view Driver::StateToStr(State state)
	{
		switch (state) 
		{
		case State::eAvailable: return "доступен";
		case State::eOnTrip:	return "в рейсе";
		case State::eResting:	return "отдыхает";
		default:				return "неизвестно";
		}
	}

	void Driver::Print() const
	{
		std::cout << "Водитель id: " << m_id
				  << ", Фамилия: " << m_fullName
				  << ", Состояние: " << StateToStr(m_state) << "\n";
	}

	void Driver::FinishTrip()
	{
		m_state = State::eAvailable;
		std::cout << "[Driver] водитель '" << m_fullName << "' завершил рейс и доступен\n";
	}

	void Driver::GoToRest()
	{
		if (m_state == State::eOnTrip)
		{
			std::cout << "[Driver] ошибка: водитель '" << m_fullName 
					  << "' в рейсе, нельзя уйти на отдых\n";
			return;
		}

		m_state = State::eResting;
		std::cout << "[Driver] водитель '" << m_fullName << "' ушёл на отдых\n";
	}
}

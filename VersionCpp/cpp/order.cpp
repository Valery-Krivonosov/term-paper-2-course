#include "../hpp/order.hpp"

#include <iostream>

namespace logistics
{
	Order::Order(std::uint64_t id, bool urgent, const Cargo& cargo)
		: m_id{ id }
		, m_urgent{ urgent }
		, m_cargo{ cargo }
	{
	}

	Order::~Order()
	{
		std::cout << "[Order] destructor: заказ id=" 
				<< m_id << " уничтожен\n";
	}

	std::string_view Order::StateToStr(State state)
	{
		switch (state)
		{
			case State::eCreated:		return "создан";
			case State::eAssigned:		return "назначен";
			case State::eInTransist:	return "в пути";
			case State::eDelivered:		return "доставлен";
			case State::eCancelled:		return "отменен";
			default:					return "не известно";
		}
	}

	void Order::Print() const
	{
		std::cout << "Заказ id=" << m_id
			<< ", срочность=" << (m_urgent ? "срочный" : "обычный")
			<< ", состояние=" << StateToStr(m_state) << "\n";

		m_cargo.Print();
		if (m_driver != nullptr)
		{
			m_driver->Print();
		}
		else
		{
			std::cout << "Водитель не назначен \n";
		}
	}

	void Order::ReleaseDriver()
	{
		if(m_driver == nullptr)
		{
			return;
		}

		m_driver->FinishTrip();

		std::cout << "[Order] заказ id=" << m_id
				<< " освободил водителя '" << m_driver->GetFullName() << "'\n";
		m_driver = nullptr;

		if (m_state == State::eAssigned || m_state == State::eInTransist)
		{
			m_state = State::eCreated;
		}
	}

	bool Order::AssignDriver(Driver& driver)
	{
		if (driver.GetState() == Driver::State::eResting)
		{
			std::cout << "[Order] отказ: водитель '" << driver.GetFullName()
					<< "' отдыхает, нельзя назначить на заказ id=" << m_id << "\n";
			return false;
		}

		if (driver.GetState() == Driver::State::eOnTrip)
		{
			std::cout << "[Order] отказ: водитель '" << driver.GetFullName()
					<< "' уже занят другим заказом\n";
			return false;
		}

		if (m_driver != nullptr && m_driver != &driver)
		{
			ReleaseDriver();
		}

		m_driver = &driver;
		driver.SetState(Driver::State::eOnTrip);
		m_state = State::eAssigned;

		std::cout << "[Order] заказ id=" << m_id
				<< " назначен на водителя '" << driver.GetFullName() << "'\n";
		return true;
	}

	bool Order::Cancel() 
	{
		if (m_state == State::eDelivered)
		{
			std::cout << "[Order] отказ: заказ id=" << m_id
					<< " уже доставлен, нельзя отменить\n";
			return false;
		}

		if (m_state == State::eCancelled)
		{
			std::cout << "[Order] отказ: заказ id=" << m_id
					<< " уже отменён\n";
			return false;
		}
	
		if (m_driver != nullptr)
		{
			m_driver->FinishTrip();
			std::cout << "[Order] заказ id=" << m_id
					<< " отменён, водитель '" << m_driver->GetFullName()
					<< "' освобождён\n";
			m_driver = nullptr;
		}
		else
		{
			std::cout << "[Order] заказ id=" << m_id << " отменён\n";
		}

		m_state = State::eCancelled;
		return true;
	}

	bool Order::StartTransit()
	{
		if (m_driver == nullptr || m_state != State::eAssigned)
		{
			std::cout << "[Order] отказ: заказ id=" << m_id
					<< " не может перейти 'в пути' без назначенного водителя\n";
			return false;
		}

		m_state = State::eInTransist;
		std::cout << "[Order] заказ id=" << m_id << " в пути\n";
		
		return true;
	}

	bool Order::Deliver()
	{
		if (m_state != State::eInTransist)
		{
			std::cout << "[Order] отказ: заказ id=" << m_id
					<< " не в пути, нельзя доставить\n";
			return false;
		}

		m_state = State::eDelivered;

		if (m_driver != nullptr)
		{
			m_driver->FinishTrip();
			std::cout << "[Order] заказ id=" << m_id
					<< " доставлен, водитель '" << m_driver->GetFullName()
					<< "' освобождён\n";
			m_driver = nullptr;
		}
		
		return true;
	}
}
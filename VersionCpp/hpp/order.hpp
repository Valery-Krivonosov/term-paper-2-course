#pragma once
	
#include "driver.hpp"
#include "cargo.hpp"

#include <cstdint>
#include <string_view>
#include <memory>


namespace logistics
{
	class Order
	{
	public:
		enum class State
		{
			eCreated = 0,
			eAssigned = 1,
			eInTransist = 2,
			eDelivered = 3,
			eCancelled = 4,
		};

	private:
		static constexpr auto TAG = "order";

		std::uint64_t m_id{ 0 };
		bool m_urgent{ false };
		State m_state{ State::eCreated };

		Cargo m_cargo{};
		std::weak_ptr<Driver> m_driver;

	public:
		Order(std::uint64_t id, bool urgent, double weightKg, std::string_view destination);
		~Order();

		Order()												= delete;
		Order(Order&&)										= delete;
		Order(const Order&)									= delete;
		Order& operator=(Order&&)							= delete;
		Order& operator=(const Order&)						= delete;

		[[nodiscard]] std::uint64_t GetId() const
		{
			return m_id;
		}

		[[nodiscard]] State GetState() const
		{
			return m_state;
		}

		[[nodiscard]] std::shared_ptr<Driver> GetDriver() const
		{
			return m_driver.lock();
		}

		[[nodiscard]] const Cargo& GetCargo() const
		{
			return m_cargo;
		}

		[[nodiscard]] bool IsUrgent() const 
		{
			return m_urgent;
		}

		void Print() const;

		void ReleaseDriver();

		bool Cancel();

		bool AssignDriver(const std::shared_ptr<Driver>&driver);

		bool StartTransit();

		bool Deliver();

	private:
		[[nodiscard]] static std::string_view StateToStr(State state);
	};
}
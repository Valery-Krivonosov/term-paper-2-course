#pragma once

#include <memory>
#include <cstdint>
#include <string>
#include <string_view>


namespace logistics
{
	class BaseVehicle 
	{
	public:
		enum class State
		{
			eAvailable = 0,
			eOnTrip = 1,
			eInRepair = 2
		};

	protected:
		std::string m_plateNumber{};
		double m_capacity{ 0 };
        int m_year{ 2020 };


		[[nodiscard]] std::string Header() const;
	
	private:
		State m_state{ State::eAvailable };
		static std::uint64_t s_lightCounter;
		static std::uint64_t s_heavyCounter;
		std::uint64_t m_id{ 0 };
		std::shared_ptr<std::string> m_docs;

		static std::uint64_t GenerateId(double capacity);

	public:
		BaseVehicle(std::string_view plateNumber, double capacity, int year);
		BaseVehicle(const BaseVehicle& other);
		BaseVehicle& operator=(const BaseVehicle& other);
		BaseVehicle(BaseVehicle&& other) noexcept;
		BaseVehicle& operator=(BaseVehicle&& other) noexcept;

		virtual ~BaseVehicle();

		[[nodiscard]] virtual std::string GetType() const = 0;

		[[nodiscard]] virtual bool PassInspection() const = 0;

		virtual std::string Describe() const;

		virtual std::unique_ptr<BaseVehicle> Clone() const = 0;

		[[nodiscard]] State GetState() const
		{
			return m_state;
		}

		[[nodiscard]] std::string GetPlateNumber() const
		{
			return m_plateNumber;
		}

		[[nodiscard]] double GetCapacity() const
		{
			return m_capacity;
		}

		[[nodiscard]] int GetYear() const
		{
			return m_year;
		}

		[[nodiscard]] std::uint64_t GetId() const
		{
			return m_id;
		}

		[[nodiscard]] std::string GetDocs() const
		{
			return *m_docs;
		}

		void SetDocs(std::string_view docs)
		{
			*m_docs = docs;
		}

		void SetState(State state)
		{
			m_state = state;
		}
	};
}

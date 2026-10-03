#pragma once

#include <cstdint>
#include <string>
#include <string_view>


namespace logistics
{

	class Driver
	{
	public:
		enum class State
		{
			eAvailable = 0,
			eOnTrip = 1,
			eResting = 2,
		};

	private:
		static constexpr auto TAG = "driver";

		std::uint64_t m_id{ 0 };
		std::string m_fullName{};
		State m_state{ State::eAvailable };

	public:
		Driver()								= default;
		Driver(const Driver&)					= default;
		Driver(Driver&&)						= default;
		Driver& operator=(const Driver&)		= default;
		Driver& operator=(Driver&&)				= default;
		Driver(std::uint64_t id, std::string_view fullName);
		~Driver();

		[[nodiscard]] std::uint64_t GetId() const
		{
			return m_id;
		}

		[[nodiscard]] std::string_view GetFullName() const
		{
			return m_fullName;
		}

		[[nodiscard]] State GetState() const
		{
			return m_state;
		}

		[[nodiscard]] bool IsAvailable() const
		{
			return m_state == State::eAvailable;
		}

		void SetState(State state)
		{
			m_state = state;
		}

		void FinishTrip();

		void GoToRest();

		void Print() const;

	private:
		[[nodiscard]] static std::string_view StateToStr(State state);
	};

}
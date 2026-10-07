#pragma once

#include <cstdint>
#include <string>
#include <string_view>


namespace logistics
{
	class Cargo
	{
	private:
		static constexpr auto TAG = "cargo";

		double m_weightKg{ 0.0 };
		std::string m_destination{};

	public:
		Cargo()							= delete;
		Cargo(Cargo&&)					= delete;
		Cargo(const Cargo&)				= delete;
		Cargo& operator=(Cargo&&)		= delete;
		Cargo& operator=(const Cargo&)  = delete;
		Cargo(double weightKg, std::string_view destination);
		~Cargo();

		[[nodiscard]] double GetWeightKg() const
		{
			return m_weightKg;
		}

		[[nodiscard]] std::string_view GetDestination() const
		{
			return m_destination;
		}

		void SetWeightKg(double weightKg);

		void Print() const;
 	};
}
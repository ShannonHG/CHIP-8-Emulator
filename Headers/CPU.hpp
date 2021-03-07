#pragma once
#include "Memory.hpp"

namespace SHG
{
	class CPU
	{
	public:
		CPU(Memory* memory);
		void Tick();

	private:
		Memory* memory;

		uint16_t programCounter;
		uint8_t stackPointer;

	};
}
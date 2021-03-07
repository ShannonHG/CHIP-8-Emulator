#include <iostream>
#include <ios>
#include <iomanip>
#include "CPU.hpp"

namespace SHG
{
	CPU::CPU(Memory* mem)
	{
		memory = mem;
		programCounter = Memory::RESERVED_MEMORY_SIZE;
	}

	void CPU::Tick()
	{
		const uint8_t* data = memory->GetData();

		//Instructions are 16 bytes each, so the bytes at [programCounter] and 
		//[programCounter + 1] are combined to retrieve the full instruction.
		uint16_t instruction = (data[programCounter] << 8) | (data[programCounter + 1]);

		//Move to next instruction
		programCounter += 2;

		std::cout << "Program counter: " << programCounter << std::endl;
		std::cout << "Current instruction: " << std::hex << std::setw(4) << instruction << std::endl;
		std::cout << std::resetiosflags(std::ios::hex);
	}
}
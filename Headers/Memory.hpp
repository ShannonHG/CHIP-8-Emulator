#pragma once
#include <string>

namespace SHG
{
	class Memory
	{
	public:
		static const int TOTAL_MEMORY = 4096;
		static const int RESERVED_MEMORY_SIZE = 512;
		static const int MAX_ROM_SIZE = TOTAL_MEMORY - RESERVED_MEMORY_SIZE;

		Memory();
		void LoadRom(std::string filePath);
		const uint8_t* GetData();

	private:
		uint8_t data[4096];
	};
}
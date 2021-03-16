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
		static const int FONT_SPRITE_SIZE = 5;
		static const int NUMBER_OF_FONT_SPRITES = 16;

		Memory();
		bool LoadRom(std::string filePath);
		const uint8_t* GetData();
		void SetByte(int address, uint8_t byte);
		uint8_t GetByte(int address);
	private:
		uint8_t data[4096]{};
	};
}
#include <fstream>
#include <iostream>
#include "Memory.hpp"

namespace SHG
{
	// Contains 16 5-byte font sprites
	static const uint8_t FONT_SPRITES[] =
	{
		// 0
		0xF0, 0x90, 0x90, 0x90, 0xF0,

		// 1
		0x20, 0x60, 0x20, 0x20, 0x70,

		// 2
		0xF0, 0x10, 0xF0, 0x80, 0xF0,

		// 3
		0xF0, 0x10, 0xF0, 0x10, 0xF0,

		// 4
		0x90, 0x90, 0xF0, 0x10, 0x10,

		// 5
		0xF0, 0x80, 0xF0, 0x10, 0xF0,

		// 6
		0xF0, 0x80, 0xF0, 0x90, 0xF0,

		// 7
		0xF0, 0x10, 0x20, 0x40, 0x40,

		// 8
		0xF0, 0x90, 0xF0, 0x90, 0xF0,

		// 9
		0xF0, 0x90, 0xF0, 0x10, 0xF0,

		// A
		0xF0, 0x90, 0xF0, 0x90, 0x90,

		// B
		0xE0, 0x90, 0xE0, 0x90, 0xE0,

		// C
		0xF0, 0x80, 0x80, 0x80, 0xF0,

		// D
		0xE0, 0x90, 0x90, 0x90, 0xE0,

		// E
		0xF0, 0x80, 0xF0, 0x80, 0xF0,

		// F
		0xF0, 0x80, 0xF0, 0x80, 0x80
	};

	Memory::Memory()
	{
		// Load font sprites into memory
		for (int i = 0; i < FONT_SPRITE_SIZE * NUMBER_OF_FONT_SPRITES; i++)
		{
			data[i] = FONT_SPRITES[i];
		}
	}

	const uint8_t* Memory::GetData()
	{
		return data;
	}

	void Memory::SetByte(int address, uint8_t byte)
	{
		data[address] = byte;
	}

	uint8_t Memory::GetByte(int address)
	{
		return data[address];
	}

	void Memory::LoadRom(std::string filePath)
	{
		std::cout << "Loading ROM: " << filePath << std::endl;

		std::ifstream file(filePath, std::fstream::binary);
		char buf[1];

		int counter = 0;
		int fileSize = 0;

		while (!file.eof())
		{
			// Read one byte from the ROM file
			file.read(buf, 1);
			
			fileSize += file.gcount();

			if (fileSize > MAX_ROM_SIZE)
			{
				std::cout << "The ROM is too large to be loaded into memory." << std::endl;
				break;
			}

			// Any memory locations after data[RESERVED_MEMORY_SIZE - 1] 
			// can be used for storing the ROM
			data[RESERVED_MEMORY_SIZE + counter] = buf[0];

			counter++;
		}

		file.close();

		std::cout << "ROM size: " << fileSize << " bytes" << std::endl;
	}
}
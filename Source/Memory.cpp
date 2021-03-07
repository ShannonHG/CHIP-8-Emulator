#include <fstream>
#include <iostream>
#include "Memory.hpp"

namespace SHG
{
	Memory::Memory()
	{
		//Load font sprites into memory
	}

	const uint8_t* Memory::GetData()
	{
		return data;
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
			//Read one byte from the ROM file
			file.read(buf, 1);
			
			fileSize += file.gcount();

			if (fileSize > MAX_ROM_SIZE)
			{
				std::cout << "The ROM is too large to be loaded into memory." << std::endl;
				break;
			}

			//Any memory locations after data[RESERVED_MEMORY_SIZE - 1] 
			//can be used for storing the ROM
			data[RESERVED_MEMORY_SIZE + counter] = buf[0];

			counter++;
		}

		file.close();

		std::cout << "ROM size: " << fileSize << " bytes" << std::endl;
	}
}
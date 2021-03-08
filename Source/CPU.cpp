#include <iostream>
#include <ios>
#include <iomanip>
#include "CPU.hpp"

namespace SHG
{
	CPU::CPU(Memory* memory, Display* display)
	{
		this->memory = memory;
		this->display = display;
	}

	void CPU::Tick()
	{
		const uint8_t* data = memory->GetData();

		// Instructions are 16 bytes each, so the bytes at [programCounter] and 
		// [programCounter + 1] are combined to retrieve the full instruction.
		uint16_t instruction = (data[programCounter] << 8) | (data[programCounter + 1]);

		// Move to next instruction
		programCounter += 2;

		std::cout << "Program counter: " << programCounter << std::endl;
		std::cout << "Instruction read from memory: " << std::hex << std::setfill('0') << std::setw(4) << instruction << std::endl;
		std::cout << std::resetiosflags(std::ios::hex);

		ExecuteInstruction(instruction, data);

		PrintStackPointerValue();
		PrintStackValues();
		PrintProgramCounterValue();
		PrintRegisterValues();
	}

	void CPU::ExecuteInstruction(uint16_t instruction, const uint8_t* memData)
	{
		switch (instruction & 0xF000) // Ignore last 12 bits
		{
		case 0x0000:
			switch (instruction)
			{
			case 0x00E0:
				Execute_00E0(instruction);
				break;
			case 0x00EE:
				Execute_00EE(instruction);
				break;
			default:
				Execute_0NNN(instruction);
				break;
			}
			break;
		case 0x1000:
			Execute_1NNN(instruction);
			break;
		case 0x2000:
			Execute_2NNN(instruction);
			break;
		case 0x3000:
			Execute_3XKK(instruction);
			break;
		case 0x4000:
			Execute_4XKK(instruction);
			break;
		case 0x5000:
			Execute_5XY0(instruction);
			break;
		case 0x6000:
			Execute_6XKK(instruction);
			break;
		case 0x7000:
			Execute_7XKK(instruction);
			break;
		case 0x8000:
			switch (instruction & 0xF00F) // Ignore middle byte
			{
			case 0x8000:
				Execute_8XY0(instruction);
				break;
			case 0x8001:
				Execute_8XY1(instruction);
				break;
			case 0x8002:
				Execute_8XY2(instruction);
				break;
			case 0x8003:
				Execute_8XY3(instruction);
				break;
			case 0x8004:
				Execute_8XY4(instruction);
				break;
			case 0x8005:
				Execute_8XY5(instruction);
				break;
			case 0x8006:
				Execute_8XY6(instruction);
				break;
			case 0x8007:
				Execute_8XY7(instruction);
				break;
			case 0x800E:
				Execute_8XYE(instruction);
				break;
			}
			break;
		case 0x9000:
			Execute_9XY0(instruction);
			break;
		case 0xA000:
			Execute_ANNN(instruction);
			break;
		case 0xB000:
			Execute_BNNN(instruction);
			break;
		case 0xC000:
			Execute_CXKK(instruction);
			break;
		case 0xD000:
			Execute_DXYN(instruction, memData);
			break;
		case 0xE000:
			switch (instruction & 0xF0FF) // Ignore second half-byte
			{
			case 0xE09E:
				Execute_EX9E(instruction);
				break;
			case 0xE0A1:
				Execute_EXA1(instruction);
				break;
			}
			break;
		case 0xF000:
			switch (instruction & 0xF0FF) // Ignore second half-byte
			{
			case 0xF007:
				Execute_FX07(instruction);
				break;
			case 0xF00A:
				Execute_FX0A(instruction);
				break;
			case 0xF015:
				Execute_FX15(instruction);
				break;
			case 0xF018:
				Execute_FX18(instruction);
				break;
			case 0xF01E:
				Execute_FX1E(instruction);
				break;
			case 0xF029:
				Execute_FX29(instruction);
				break;
			case 0xF033:
				Execute_FX33(instruction);
				break;
			case 0xF055:
				Execute_FX55(instruction);
				break;
			case 0xF065:
				Execute_FX65(instruction);
				break;
			}
			break;
		}
	}

	void CPU::Execute_0NNN(uint16_t instruction)
	{
		PrintInstructionExecution("0NNN");
	}

	void CPU::Execute_00E0(uint16_t instruction)
	{
		PrintInstructionExecution("00E0");

		display->Clear();
	}

	void CPU::Execute_00EE(uint16_t instruction)
	{
		PrintInstructionExecution("00EE");

		programCounter = stack[stackPointer];
		stackPointer--;
	}

	void CPU::Execute_1NNN(uint16_t instruction)
	{
		PrintInstructionExecution("1NNN");

		programCounter = instruction & 0x0FFF;
	}

	void CPU::Execute_2NNN(uint16_t instruction)
	{
		PrintInstructionExecution("2NNN");

		stackPointer++;
		programCounter = stack[stackPointer];
	}

	void CPU::Execute_3XKK(uint16_t instruction)
	{
		PrintInstructionExecution("3XKK");

		// If Vx is equal to kk, then skip the next instruction
		if (vRegisters[GetXRegisterId(instruction)] == (instruction & 0x00FF)) programCounter += 2;
	}

	void CPU::Execute_4XKK(uint16_t instruction)
	{
		PrintInstructionExecution("4XKK");

		// If Vx is NOT equal to kk, then skip the next instruction
		if (vRegisters[GetXRegisterId(instruction)] != (instruction & 0x00FF)) programCounter += 2;
	}

	void CPU::Execute_5XY0(uint16_t instruction)
	{
		PrintInstructionExecution("5XY0");

		//If Vx is equal to Vy, then skip the next instruction
		if (vRegisters[GetXRegisterId(instruction)] == vRegisters[GetYRegisterId(instruction)]) programCounter += 2;
	}

	void CPU::Execute_6XKK(uint16_t instruction)
	{
		PrintInstructionExecution("6XKK");

		uint8_t xRegId = GetXRegisterId(instruction);
		vRegisters[xRegId] = instruction & 0x00FF;
	}

	void CPU::Execute_7XKK(uint16_t instruction)
	{
		PrintInstructionExecution("7XKK");

		uint8_t xRegId = GetXRegisterId(instruction);
		vRegisters[xRegId] += instruction & 0x00FF;
	}

	void CPU::Execute_8XY0(uint16_t instruction)
	{
		PrintInstructionExecution("8XY0");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);
		vRegisters[xRegId] = vRegisters[yRegId];
	}

	void CPU::Execute_8XY1(uint16_t instruction)
	{
		PrintInstructionExecution("8XY1");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);
		vRegisters[xRegId] |= vRegisters[yRegId];
	}

	void CPU::Execute_8XY2(uint16_t instruction)
	{
		PrintInstructionExecution("8XY2");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);
		vRegisters[xRegId] = vRegisters[xRegId] & vRegisters[yRegId];
	}

	void CPU::Execute_8XY3(uint16_t instruction)
	{
		PrintInstructionExecution("8XY3");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);

		// XOR
		vRegisters[xRegId] ^= vRegisters[xRegId] & vRegisters[yRegId];
	}

	void CPU::Execute_8XY4(uint16_t instruction)
	{
		PrintInstructionExecution("8XY4");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);

		uint16_t sum = vRegisters[xRegId] + vRegisters[yRegId];

		// Store lower 8 bits in the register
		vRegisters[xRegId] = sum & 0xFF;

		// If the sum is greater than 0, then set VF to 1
		if (sum > 255) vRegisters[VF_REG_INDEX] = 1;
	}

	void CPU::Execute_8XY5(uint16_t instruction)
	{
		PrintInstructionExecution("8XY5");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);

		// If Vx is greater than Vy, then set VF to 1, otherwise set VF to 0
		vRegisters[VF_REG_INDEX] = vRegisters[xRegId] > vRegisters[yRegId] ? 1 : 0;

		vRegisters[xRegId] -= vRegisters[yRegId];
	}

	void CPU::Execute_8XY6(uint16_t instruction)
	{
		PrintInstructionExecution("8XY6");

		uint8_t xRegId = GetXRegisterId(instruction);

		// If the least significant bit of Vx is 1, then set the VF to 1, otherwise set VF to 0
		vRegisters[VF_REG_INDEX] = (vRegisters[xRegId] & 1) == 1 ? 1 : 0;

		vRegisters[xRegId] /= 2;
	}

	void CPU::Execute_8XY7(uint16_t instruction)
	{
		PrintInstructionExecution("8XY7");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);

		vRegisters[VF_REG_INDEX] = vRegisters[yRegId] > vRegisters[xRegId] ? 1 : 0;
		vRegisters[xRegId] = vRegisters[yRegId] - vRegisters[xRegId];
	}

	void CPU::Execute_8XYE(uint16_t instruction)
	{
		PrintInstructionExecution("8XYE");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);

		// If the most significant bit of Vx is 1, then set VF to 1, otherwise set VF to 0
		// 128 (decimal) = 10000000 (binary)
		vRegisters[VF_REG_INDEX] = (vRegisters[xRegId] & 128) == 1 ? 1 : 0;

		vRegisters[xRegId] *= 2;
	}

	void CPU::Execute_9XY0(uint16_t instruction)
	{
		PrintInstructionExecution("9XY0");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);

		// If Vx is NOT equal to Vy, then skip the next instruction
		if (vRegisters[xRegId] != vRegisters[yRegId]) programCounter += 2;
	}

	void CPU::Execute_ANNN(uint16_t instruction)
	{
		PrintInstructionExecution("ANNN");

		iRegister = instruction & 0x0FFF;

		std::cout << "Register 'I' updated: " << iRegister << std::endl;
	}

	void CPU::Execute_BNNN(uint16_t instruction)
	{
		PrintInstructionExecution("BNNN");

		programCounter = (instruction & 0x0FFF) + vRegisters[0];
	}

	void CPU::Execute_CXKK(uint16_t instruction)
	{
		PrintInstructionExecution("CXKK");

		uint8_t xRegId = GetXRegisterId(instruction);

		//TODO: Use a better method of getting random numbers
		uint8_t randNum = rand() % 255;

		vRegisters[xRegId] = randNum & instruction & 0x00FF;
	}

	void CPU::Execute_DXYN(uint16_t instruction, const uint8_t* memData)
	{
		PrintInstructionExecution("DXYN");

		uint8_t xRegId = GetXRegisterId(instruction);
		uint8_t yRegId = GetYRegisterId(instruction);
		uint16_t spriteSize = instruction & 0x000F;

		std::cout << "Drawing sprite with size: 8 x " << spriteSize << std::endl;

		int x = vRegisters[xRegId];

		for (int index = 0; index < spriteSize; index++)
		{
			int y = vRegisters[yRegId] + index;

			uint8_t spriteByte = memData[iRegister + index];

			for (int i = 0; i < 8; i++)
			{
				// Note: Bits should be read from left to right since graphics on CHIP-8 are drawn
				// from top-left to bottom-right. 

				// This operation is done in order to isolate the bit that represents
				// the current pixel.
				// 0x80(hexadecimal) = 128(decimal) = 10000000(binary).
				uint8_t pixel = spriteByte & (0x80 >> i);

				// Shift the isolated bit to the right-most position in the byte, so 
				// that the byte can be treated as a 0 or 1.
				pixel = pixel >> (7 - i);

				display->SetPixel(x + i, y, pixel);
			}
		}
	}


	void CPU::Execute_EX9E(uint16_t instruction)
	{
		PrintInstructionExecution("EX9E");

		// TODO: Implement
	}

	void CPU::Execute_EXA1(uint16_t instruction)
	{
		PrintInstructionExecution("EXA1");

		// TODO: Check if key with value Vx is pressed. If it's not pressed, skip next instruction.
		programCounter += 2;
	}

	void CPU::Execute_FX07(uint16_t instruction)
	{
		PrintInstructionExecution("FX07");

		uint8_t xRegId = GetXRegisterId(instruction);

		vRegisters[xRegId] = timerRegisters[DELAY_TIMER_INDEX];
	}

	void CPU::Execute_FX0A(uint16_t instruction)
	{
		PrintInstructionExecution("FX0A");

		uint8_t xRegId = GetXRegisterId(instruction);

		// TODO: Implement
	}

	void CPU::Execute_FX15(uint16_t instruction)
	{
		PrintInstructionExecution("FX15");

		uint8_t xRegId = GetXRegisterId(instruction);

		timerRegisters[DELAY_TIMER_INDEX] = vRegisters[xRegId];

		std::cout << "Updated delay timer register: " << timerRegisters[DELAY_TIMER_INDEX] << std::endl;
	}

	void CPU::Execute_FX18(uint16_t instruction)
	{
		PrintInstructionExecution("FX18");

		uint8_t xRegId = GetXRegisterId(instruction);

		timerRegisters[SOUND_TIMER_INDEX] = vRegisters[xRegId];

		std::cout << "Updated sound timer register: " << timerRegisters[SOUND_TIMER_INDEX] << std::endl;
	}

	void CPU::Execute_FX1E(uint16_t instruction)
	{
		PrintInstructionExecution("FX1E");

		uint8_t xRegId = GetXRegisterId(instruction);

		iRegister += vRegisters[xRegId];
	}

	void CPU::Execute_FX29(uint16_t instruction)
	{
		PrintInstructionExecution("FX29");

		// TODO: Implement
	}

	void CPU::Execute_FX33(uint16_t instruction)
	{
		PrintInstructionExecution("FX33");

		// TODO: Implement
	}

	void CPU::Execute_FX55(uint16_t instruction)
	{
		PrintInstructionExecution("FX55");

		// TODO: Implement
	}

	void CPU::Execute_FX65(uint16_t instruction)
	{
		PrintInstructionExecution("FX65");

		// TODO: Implement
	}

	void CPU::PrintInstructionExecution(std::string instruction)
	{
		std::cout << "[Executing instruction: " << instruction << "]" << std::endl;
	}

	void CPU::PrintStackValues()
	{
		std::cout << "Stack: [";

		for (int i = 0; i < 16; i++)
		{
			std::cout << (int)stack[i];
			if (i < 15) std::cout << ", ";
		}

		std::cout << "]" << std::endl;
	}

	void CPU::PrintStackPointerValue()
	{
		std::cout << "Stack pointer: " << (int)stackPointer << std::endl;
	}

	void CPU::PrintProgramCounterValue()
	{
		std::cout << "Program counter: " << (int)programCounter << std::endl;
	}

	void CPU::PrintRegisterValues()
	{
		std::cout << "I Register: " << (int)iRegister << std::endl;
		std::cout << "Delay register: " << (int)timerRegisters[DELAY_TIMER_INDEX] << std::endl;
		std::cout << "Sound register: " << (int)timerRegisters[SOUND_TIMER_INDEX] << std::endl;
		std::cout << "V Registers: [";

		for (int i = 0; i < 16; i++)
		{
			std::cout << (int)vRegisters[i];
			if (i < 15) std::cout << ", ";
		}
		
		std::cout << "]" << std::endl;
	}

	uint8_t CPU::GetXRegisterId(uint16_t instruction)
	{
		// The 'X' register ID is generally stored in the second highest half-byte.
		// The value is shifted to the right by 8 bits in order to get the actual integer value.
		return (instruction & 0x0F00) >> 8;
	}

	uint8_t CPU::GetYRegisterId(uint16_t instruction)
	{
		// The 'Y' register ID is generally stored in the second lowest half-byte.
		// The value is shifted to the right by 4 bits in order to get the actual integer value.
		return (instruction & 0x00F0) >> 4;
	}
}
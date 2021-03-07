#pragma once
#include <map>
#include <functional>
#include "Memory.hpp"

namespace SHG
{
	class CPU
	{
	public:
		CPU(Memory* memory);
		void Tick();

	private:
		static const uint8_t STACK_SIZE = 16;
		static const uint8_t REGISTER_COUNT = 16;
		static const uint8_t DELAY_TIMER_INDEX = 0;
		static const uint8_t SOUND_TIMER_INDEX = 1;
		static const uint8_t VF_REG_INDEX = 15;

		Memory* memory;
		uint16_t programCounter = Memory::RESERVED_MEMORY_SIZE;
		uint16_t stack[STACK_SIZE]{};
		uint8_t stackPointer{};
		uint8_t vRegisters[REGISTER_COUNT]{};
		uint16_t iRegister{};
		uint16_t timerRegisters[2]{};

		void LogInstructionExecution(std::string instruction);
		void LogStackPointerUpdate();
		void LogProgramCounterUpdate();
		void LogRegisterUpdate(int id);

		void ExecuteInstruction(uint16_t, const uint8_t*);

		//SYS addr
		void Execute_0NNN(uint16_t);

		//CLS
		void Execute_00E0(uint16_t);

		//RET
		void Execute_00EE(uint16_t);

		//JP addr
		void Execute_1NNN(uint16_t);

		//CALL addr
		void Execute_2NNN(uint16_t);

		//SE Vx, byte
		void Execute_3XKK(uint16_t);

		//SNE Vx, byte
		void Execute_4XKK(uint16_t);

		//SE Vx, Vy
		void Execute_5XY0(uint16_t);

		//LD Vx, byte
		void Execute_6XKK(uint16_t);

		//ADD vx, byte
		void Execute_7XKK(uint16_t);

		//LD Vx, Vy
		void Execute_8XY0(uint16_t);

		//OR VX, Vy
		void Execute_8XY1(uint16_t);

		//AND Vx, Vy
		void Execute_8XY2(uint16_t);

		//XOR Vx, Vy
		void Execute_8XY3(uint16_t);

		//ADD Vx, Vy
		void Execute_8XY4(uint16_t);

		//SUB Vx, Vy
		void Execute_8XY5(uint16_t);

		//SHR Vx {, Vy}
		void Execute_8XY6(uint16_t);

		//SUBN V, Vy
		void Execute_8XY7(uint16_t);

		//SHL vx {, Vy}
		void Execute_8XYE(uint16_t);

		//SNE Vx, Vy
		void Execute_9XY0(uint16_t);

		//LD I, addr
		void Execute_ANNN(uint16_t);

		//JP V0, addr
		void Execute_BNNN(uint16_t);

		//RND Vx, byte
		void Execute_CXKK(uint16_t);

		//DRW Vx, Vy, nibble
		void Execute_DXYN(uint16_t, const uint8_t*);

		//SKP Vx
		void Execute_EX9E(uint16_t);

		//SKNP Vx
		void Execute_EXA1(uint16_t);

		//SKNP Vx
		void Execute_FX07(uint16_t);

		//LD Vx, K
		void Execute_FX0A(uint16_t);

		//LD DT, Vx
		void Execute_FX15(uint16_t);

		//LD ST, Vx
		void Execute_FX18(uint16_t);

		//ADD I, Vx
		void Execute_FX1E(uint16_t);

		//LD F, Vx
		void Execute_FX29(uint16_t);

		//LD B, Vx
		void Execute_FX33(uint16_t);

		//LD [I], Vx
		void Execute_FX55(uint16_t);

		//LD Vx, [I]
		void Execute_FX65(uint16_t);
	};
}
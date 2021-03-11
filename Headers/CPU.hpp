#pragma once
#include <map>
#include <functional>
#include <chrono>
#include "Memory.hpp"
#include "Display.hpp"
#include "Keypad.hpp"

namespace SHG
{
	class CPU
	{
	public:
		CPU(Memory* memory, Display* display, Keypad* keypad);
		void StartCycle(int instructionsPerSecond);
		void Tick();

	private:
		static const uint8_t STACK_SIZE = 16;
		static const uint8_t REGISTER_COUNT = 16;
		static const uint8_t DELAY_TIMER_INDEX = 0;
		static const uint8_t SOUND_TIMER_INDEX = 1;
		static const uint8_t VF_REG_INDEX = 15;

		Memory* memory;
		Display* display;
		Keypad* keypad;
		uint16_t programCounter = Memory::RESERVED_MEMORY_SIZE;
		uint16_t stack[STACK_SIZE]{};
		uint8_t stackPointer{};
		uint8_t vRegisters[REGISTER_COUNT]{};
		uint16_t iRegister{};
		uint16_t timerRegisters[2]{};

		std::chrono::system_clock::time_point previousTimerUpdateTime;

		bool isRunning = false;
		int instructionsPerSecond = 800;
		double targetFetchDeltaTime;
		std::chrono::system_clock::time_point previousInstructionFetchTime;

		uint8_t GetX(uint16_t instruction);
		uint8_t GetY(uint16_t instruction);

		void PrintInstructionExecution(std::string instruction);
		void PrintStackPointerValue();
		void PrintStackValues();
		void PrintProgramCounterValue();
		void PrintRegisterValues();
		void PrintDelayTimerValue();
		void PrintSoundTimerValue();

		void MoveToNextInstruction();
		void ExecuteInstruction(uint16_t instruction);

		//SYS addr
		void Execute_0NNN(uint16_t instruction);

		//CLS
		void Execute_00E0(uint16_t instruction);

		//RET
		void Execute_00EE(uint16_t instruction);

		//JP addr
		void Execute_1NNN(uint16_t instruction);

		//CALL addr
		void Execute_2NNN(uint16_t instruction);

		//SE Vx, byte
		void Execute_3XKK(uint16_t instruction);

		//SNE Vx, byte
		void Execute_4XKK(uint16_t instruction);

		//SE Vx, Vy
		void Execute_5XY0(uint16_t instruction);

		//LD Vx, byte
		void Execute_6XKK(uint16_t instruction);

		//ADD vx, byte
		void Execute_7XKK(uint16_t instruction);

		//LD Vx, Vy
		void Execute_8XY0(uint16_t instruction);

		//OR VX, Vy
		void Execute_8XY1(uint16_t instruction);

		//AND Vx, Vy
		void Execute_8XY2(uint16_t instruction);

		//XOR Vx, Vy
		void Execute_8XY3(uint16_t instruction);

		//ADD Vx, Vy
		void Execute_8XY4(uint16_t instruction);

		//SUB Vx, Vy
		void Execute_8XY5(uint16_t instruction);

		//SHR Vx {, Vy}
		void Execute_8XY6(uint16_t instruction);

		//SUBN V, Vy
		void Execute_8XY7(uint16_t instruction);

		//SHL vx {, Vy}
		void Execute_8XYE(uint16_t instruction);

		//SNE Vx, Vy
		void Execute_9XY0(uint16_t instruction);

		//LD I, addr
		void Execute_ANNN(uint16_t instruction);

		//JP V0, addr
		void Execute_BNNN(uint16_t instruction);

		//RND Vx, byte
		void Execute_CXKK(uint16_t instruction);

		//DRW Vx, Vy, nibble
		void Execute_DXYN(uint16_t instruction);

		//SKP Vx
		void Execute_EX9E(uint16_t instruction);

		//SKNP Vx
		void Execute_EXA1(uint16_t instruction);

		//SKNP Vx
		void Execute_FX07(uint16_t instruction);

		//LD Vx, K
		void Execute_FX0A(uint16_t instruction);

		//LD DT, Vx
		void Execute_FX15(uint16_t instruction);

		//LD ST, Vx
		void Execute_FX18(uint16_t instruction);

		//ADD I, Vx
		void Execute_FX1E(uint16_t instruction);

		//LD F, Vx
		void Execute_FX29(uint16_t instruction);

		//LD B, Vx
		void Execute_FX33(uint16_t instruction);

		//LD [I], Vx
		void Execute_FX55(uint16_t instruction);

		//LD Vx, [I]
		void Execute_FX65(uint16_t instruction);
	};
}
#include <iostream>
#include <chrono>
#include <SDL.h>
#include "Memory.hpp"
#include "Display.hpp"
#include "Keypad.hpp"
#include "CPU.hpp"

using namespace std::chrono;

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 320;
static const int ROM_PATH_INDEX = 1;
static const int INSTRUCTIONS_PER_SECOND_INDEX = 2;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "No ROM file provided. Shutting Down..." << std::endl;
		return 0;
	}

	SHG::Memory memory = SHG::Memory();
	if (!memory.LoadRom(argv[ROM_PATH_INDEX])) return 0;

	SHG::Display display = SHG::Display(SCREEN_WIDTH, SCREEN_HEIGHT);
	SHG::Keypad keypad = SHG::Keypad();

	int instructionsPerSecond = 60;

	if (argc > 2)
	{
		try
		{
			instructionsPerSecond = std::stoi(argv[INSTRUCTIONS_PER_SECOND_INDEX]);
		}
		catch (std::exception const e)
		{
			std::cout << "Invalid value provided for 'instructionsPerSecond'. Setting to default value." << std::endl;
		}
	}

	std::cout << "Instructions per second: " << instructionsPerSecond << std::endl;

	SHG::CPU cpu = SHG::CPU(&memory, &display, &keypad);
	cpu.StartCycle(instructionsPerSecond);

	return 0;
}
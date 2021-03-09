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

int main(int argc, char* argv[])
{
	SHG::Memory memory = SHG::Memory();
	memory.LoadRom(argv[ROM_PATH_INDEX]);

	SHG::Display display = SHG::Display(SCREEN_WIDTH, SCREEN_HEIGHT);
	SHG::Keypad keypad = SHG::Keypad();

	SHG::CPU cpu = SHG::CPU(&memory, &display, &keypad);

	bool isRunning = true;
	auto previousTime = system_clock::now();

	while (isRunning)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			keypad.Update(e);
		}

		cpu.Tick();
	}

	return 0;
}
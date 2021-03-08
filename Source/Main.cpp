#include <iostream>
#include <chrono>
#include <SDL.h>
#include "Memory.hpp"
#include "Display.hpp"
#include "CPU.hpp"

using namespace std::chrono;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;
const int TARGET_FPS = 60;
const double TARGET_DELTA_TIME = (1.0 / TARGET_FPS) * 1000.0;

int main(int argc, char* argv[])
{
	SHG::Memory memory = SHG::Memory();
	memory.LoadRom(argv[1]);

	SHG::Display display = SHG::Display(SCREEN_WIDTH, SCREEN_HEIGHT);

	SHG::CPU cpu = SHG::CPU(&memory, &display);

	bool isRunning = true;
	auto previousTime = system_clock::now();

	while (isRunning)
	{
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent))
		{
			// TODO: Process events
		}

		auto currentTime = system_clock::now();

		// Get the delta time between the current time point and the last tick, in milliseconds and as a double
		auto deltaTime = (duration_cast<duration<double, std::milli>> (currentTime - previousTime)).count();

		if (deltaTime >= TARGET_DELTA_TIME)
		{
			std::cout << std::endl << "Delta time: " << deltaTime << " ms" << std::endl;

			cpu.Tick();

			previousTime = currentTime;
		}
	}

	return 0;
}
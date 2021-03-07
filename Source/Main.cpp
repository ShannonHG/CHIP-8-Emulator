#include <iostream>
#include <chrono>
#include "Memory.hpp"
#include "CPU.hpp"

using namespace std::chrono;

int main(int argc, char* argv[])
{
	SHG::Memory memory = SHG::Memory();
	memory.LoadRom(argv[1]);

	SHG::CPU cpu = SHG::CPU(&memory);

	bool isRunning = true;
	auto previousTime = system_clock::now();

	int targetFPS = 60;
	double targetDeltaTime = (1.0 / targetFPS) * 1000.0;

	while (isRunning)
	{
		auto currentTime = system_clock::now();

		//Get the delta time between the current time point and the last tick, in milliseconds and as a double
		auto deltaTime = (duration_cast<duration<double, std::milli>> (currentTime - previousTime)).count();

		if (deltaTime >= targetDeltaTime)
		{
			std::cout << std::endl << "Delta time: " << deltaTime << std::endl;

			cpu.Tick();

			previousTime = currentTime;
		}
	}

	return 0;
}
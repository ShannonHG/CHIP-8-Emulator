#pragma once
#include <cstdint>
#include <map>
#include <SDL.h>

namespace SHG
{
	class Keypad
	{
	public:
		Keypad();
		bool IsKeyPressed(uint8_t key);
		void Update(SDL_Event e);
		bool GetKeyPressedThisFrame(uint8_t* key);

	private:
		std::map<uint8_t, bool> keyStates;
	};
}
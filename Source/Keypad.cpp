#include <map>
#include <iostream>
#include <iomanip>
#include "Keypad.hpp"

namespace SHG
{
	static const std::map<SDL_Keycode, uint8_t> KEYS =
	{
		{SDLK_1, 0x1}, {SDLK_2, 0x2},    {SDLK_3, 0x3},		{SDLK_4, 0xC},
		{SDLK_q, 0x4}, {SDLK_w, 0x5},    {SDLK_e, 0x6},     {SDLK_r, 0xD},
		{SDLK_a, 0x7}, {SDLK_s, 0x8},    {SDLK_d, 0x9},     {SDLK_f, 0xE},
		{SDLK_z, 0xA}, {SDLK_x, 0x0},	 {SDLK_c, 0xB},		{SDLK_v, 0xF}
	};

	Keypad::Keypad()
	{
		for (int i = 0; i < 16; i++) keyStates[i] = false;
	}

	bool Keypad::IsKeyPressed(uint8_t key)
	{
		return keyStates[key];
	}

	void Keypad::Update(SDL_Event e)
	{
		SDL_Keycode keyCode = e.key.keysym.sym;
		if (KEYS.count(keyCode) == 0) return;

		if (e.type == SDL_KEYDOWN)
		{
			keyStates[KEYS.at(keyCode)] = true;

			/*std::cout << "Detected key press: " << std::hex << std::setfill('0') << std::setw(2) << (int)KEYS.at(e.key.keysym.sym) << std::endl;
			std::cout << std::resetiosflags(std::ios::hex);*/
		}
		else if (e.type == SDL_KEYUP)
		{
			keyStates[KEYS.at(keyCode)] = false;
		}
	}

	bool Keypad::GetKeyPressedThisFrame(uint8_t* key)
	{
		for (int i = 0; i < 16; i++)
		{
			if (keyStates[i])
			{
				*key = i;
				return true;
			}
		}

		return false;
	}
}
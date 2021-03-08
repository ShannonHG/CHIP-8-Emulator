#pragma once
#include <cstdint>
#include <SDL.h>

namespace SHG
{
	class Display
	{
	public: 
		Display(int width, int height);
		void Clear();
		void SetPixel(int x, int y, uint8_t color);
		uint8_t GetPixel(int x, int y);

	private:
		static const int CHIP_8_SCREEN_WIDTH = 64;
		static const int CHIP_8_SCREEN_HEIGHT = 32;

		uint8_t nativeScreenPixels[CHIP_8_SCREEN_WIDTH * CHIP_8_SCREEN_HEIGHT]{};

		int screenWidth{};
		int screenHeight{};

		SDL_Window* window{};
		SDL_Surface* surface{};
		SDL_Renderer* renderer{};
	};
}
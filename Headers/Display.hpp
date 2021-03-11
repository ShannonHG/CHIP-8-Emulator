#pragma once
#include <cstdint>
#include <SDL.h>

namespace SHG
{
	class Display
	{
	public: 
		static const int LOW_RES_SCREEN_WIDTH = 64;
		static const int LOW_RES_SCREEN_HEIGHT = 32;
		static const int LOW_RES_PIXEL_COUNT = LOW_RES_SCREEN_WIDTH * LOW_RES_SCREEN_HEIGHT;

		Display(int width, int height);
		void Clear();
		void SetPixel(int x, int y, uint8_t color);
		uint8_t GetPixel(int x, int y);

	private:
		uint8_t lowResScreenPixels[LOW_RES_PIXEL_COUNT]{};

		int screenWidth{};
		int screenHeight{};

		int pixelWidth{};
		int pixelHeight{};

		SDL_Window* window{};
		SDL_Surface* surface{};
		SDL_Renderer* renderer{};
	};
}
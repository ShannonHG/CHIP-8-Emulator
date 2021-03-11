#include <iostream>
#include "Display.hpp"

namespace SHG
{
	Display::Display(int width, int height)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
			return;
		}

		screenWidth = width;
		screenHeight = height;

		// Since a screen size significantly larger than CHIP-8's native screen size is used, 
		// the pixels have to be 'scaled' up in order to be rendered correctly.
		pixelWidth = screenWidth / LOW_RES_SCREEN_WIDTH;
		pixelHeight = screenHeight / LOW_RES_SCREEN_HEIGHT;

		window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, 0, 0);
		surface = SDL_GetWindowSurface(window);
	}

	void Display::Clear()
	{
		std::fill(lowResScreenPixels, lowResScreenPixels + LOW_RES_PIXEL_COUNT, 0);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	void Display::SetPixel(int x, int y, uint8_t bit)
	{
		if (x >= LOW_RES_SCREEN_WIDTH || y >= LOW_RES_SCREEN_HEIGHT) return;

		lowResScreenPixels[x + (y * LOW_RES_SCREEN_WIDTH)] = bit & 1;

		uint8_t color = (bit & 1) * 255;

		SDL_Rect rect;
		rect.x = x * pixelWidth;
		rect.y = y * pixelHeight;
		rect.w = pixelWidth;
		rect.h = pixelHeight;

		SDL_SetRenderDrawColor(renderer, color, color, color, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);
		
	}

	uint8_t Display::GetPixel(int x, int y)
	{
		if (x >= LOW_RES_SCREEN_WIDTH || y >= LOW_RES_SCREEN_HEIGHT) return 0;

		return lowResScreenPixels[x + (y * LOW_RES_SCREEN_WIDTH)];
	}
}
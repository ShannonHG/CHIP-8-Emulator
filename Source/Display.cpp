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

		window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, 0, 0);
		surface = SDL_GetWindowSurface(window);
	}

	void Display::Clear()
	{
		for (int i = 0; i < LOW_RES_PIXEL_COUNT; i++) lowResScreenPixels[i] = 0;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	void Display::SetPixel(int x, int y, uint8_t bit)
	{
		lowResScreenPixels[x + (y * LOW_RES_SCREEN_WIDTH)] = bit & 1;

		uint8_t color = (bit & 1) * 255;

		// Since a screen size significantly larger than CHIP-8's native screen size is used, 
		// the pixels have to be 'scaled' up in order to be rendered correctly.
		int pixelWidth = screenWidth / LOW_RES_SCREEN_WIDTH;
		int pixelHeight = screenHeight / LOW_RES_SCREEN_HEIGHT;

		// Using the pixelWidth and pixelHeight, a grid of pixels is drawn relative to the original
		// pixel's x and y coordinates.
		for (int px = 0; px < pixelWidth; px++)
		{
			for (int py = 0; py < pixelHeight; py++)
			{
				SDL_SetRenderDrawColor(renderer, color, color, color, 255);
				SDL_RenderDrawPoint(renderer, (x * pixelWidth) + px, (y * pixelHeight) + py);
			}
		}

		SDL_RenderPresent(renderer);
	}

	uint8_t Display::GetPixel(int x, int y)
	{
		return lowResScreenPixels[x + (y * LOW_RES_SCREEN_WIDTH)];
	}
}
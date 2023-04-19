#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// #define THING_X 100
// #define THING_Y 100
#define THING_WIDTH 100
#define THING_HEIGHT THING_WIDTH
#define SPEED 7

int thing_x = 100;
int thing_y = 100;
int thing_dx = 1;
int thing_dy = 1;

const int FPS = 60;
Uint32 elapsed = 0;
int dt = 0;

int main()
{
	// initialize sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
	}

	// create window
	SDL_Window *window = SDL_CreateWindow("bouncy box thing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (!window) {
		fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
	}

	// create renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
	}

	// main loop
	bool isRunning = true;
	while (isRunning) {
		elapsed = SDL_GetTicks();
		// printf("elapsed: %d\n", elapsed);
		// INPUT
		// handling events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					{
						isRunning = false;
						break;
					}
					
				default:
					break;
      }
		}

		// UPDATE

		if ((thing_x <= 0) || (thing_x >= WINDOW_WIDTH - THING_WIDTH)) thing_dx *= -1;
		if ((thing_y <= 0) || (thing_y >= WINDOW_HEIGHT - THING_HEIGHT)) thing_dy *= -1;

		thing_x += thing_dx*SPEED;
		thing_y += thing_dy*SPEED;

		SDL_Rect thing = {
			.x = thing_x,
			.y = thing_y,
			.w = THING_WIDTH,
			.h = THING_HEIGHT,
		};

		// RENDER / DISPLAY
		// clear screen
		SDL_RenderClear(renderer);

		// display out thing
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderFillRect(renderer, &thing);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		// display the stuff i guess...?
		SDL_RenderPresent(renderer);

		// capping our framerate to the desired FPS
		dt = SDL_GetTicks() - elapsed;
		// here, we check if the time taken for one frame is less than the time taken for one frame in 60FPS
		if (dt < (1000/FPS)) {
			// if it is, then we delay
			SDL_Delay((1000/FPS) - dt);
		}
	}	

	// destroy window
	SDL_DestroyWindow(window);
	// close sdl
	SDL_Quit();
	return 0;
}

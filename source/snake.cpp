
#include "snake.hpp"

Snake::Snake() :
	io ("./snakeLog"),
	backgroundColor {0, 0, 0, 255},
	running (true)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw InitError("SDL");

	window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
	if (!window)
		throw InitError("SDL window");

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
		throw InitError("SDL renderer");

	io.output(SisIO::messageType::okay, "Game started successfully.");
}

void Snake::pollEvents() {
	SDL_Event event = {0};
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			running = false;
	}
}

void Snake::updateScreen() {
	SET_DRAW_COLOR(renderer, backgroundColor);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

Snake::~Snake() {
	SDL_Quit();
	io.output(SisIO::messageType::okay, "Game ended successfully.");
}

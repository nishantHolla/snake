
#include "snake.hpp"

Snake::Snake() :
	io ("./snakeLog"),
	backgroundColor {0, 0, 0, 255},
	borderColor {255, 255, 255, 255},
	snakeColor {255, 0, 0, 255}
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw InitError("SDL");

	window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
	if (!window)
		throw InitError("SDL window");

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
		throw InitError("SDL renderer");

	running = true;
	makeCell(snakeHead, START_X, START_Y);
	direction = {1, 0};

	io.output(SisIO::messageType::okay, "Game started successfully.");
}

void Snake::startFrame() {
	startTick = SDL_GetPerformanceCounter();
}

void Snake::pollEvents() {
	SDL_Event event = {0};
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
			continue;
		}

		int key = -1;
		if (event.type == SDL_KEYDOWN)
			key = event.key.keysym.sym;

		if (key == SDLK_DOWN)
			direction = {0, 1};

		else if (key == SDLK_RIGHT)
			direction = {1, 0};

		else if (key == SDLK_LEFT)
			direction = {-1, 0};

		else if (key == SDLK_UP)
			direction = {0, -1};
	}
}

void Snake::update() {
	snakeHead.x += (CELL_WIDTH * direction.x);
	snakeHead.y += (CELL_WIDTH * direction.y);
}

void Snake::show() {
	SET_DRAW_COLOR(renderer, backgroundColor);
	SDL_RenderClear(renderer);

	SET_DRAW_COLOR(renderer, borderColor);
	SDL_RenderDrawLine(renderer, 0, START_Y, WINDOW_WIDTH, START_Y);

	showCell(snakeHead, snakeColor);

	SDL_RenderPresent(renderer);
}

void Snake::endFrame() {
	endTick = SDL_GetPerformanceCounter();

	float elapsedMS = (endTick - startTick) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
	SDL_Delay(floor(FRAME_TARGET - elapsedMS));
}

void Snake::makeCell(SDL_Rect& _rect, int _x, int _y) {
	_rect.x = _x + (PADDING/2);
	_rect.y = _y + (PADDING/2);
	_rect.w = CELL_WIDTH - PADDING;
	_rect.h = CELL_HEIGHT - PADDING;
}

void Snake::showCell(SDL_Rect& _rect, SDL_Color& _color) {
	SET_DRAW_COLOR(renderer, _color);
	SDL_RenderFillRect(renderer, &_rect);
	SDL_RenderDrawRect(renderer, &_rect);
}

Snake::~Snake() {
	SDL_Quit();
	io.output(SisIO::messageType::okay, "Game ended successfully.");
}

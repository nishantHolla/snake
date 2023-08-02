
#ifndef SNAKE_H_
#define SNAKE_H_

#include <exception>
#include <string>
#include <SDL2/SDL.h>
#include "sisIO.hpp"

#define WINDOW_TITLE "Snake"
#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_FLAGS SDL_WINDOW_SHOWN

#define SET_DRAW_COLOR(x, y) SDL_SetRenderDrawColor(x, y.r, y.g, y.b, y.a)

class Snake {
public:
	Snake();
	bool isRunning() {return running;};
	void pollEvents();
	void updateScreen();
	~Snake();

private:
	SisIO io;

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Color backgroundColor;

	bool running;

	class InitError : public std::exception {
	public:
		InitError(const char* _source) :
			source (_source)
		{ };

		const std::string what() {return "Failed to initialize " + std::string(source) + "." + SDL_GetError();}

	private:
		const char* source;
	};
};

#endif //!SNAKE_H_


#ifndef SNAKE_H_
#define SNAKE_H_

#include <exception>
#include <string>
#include <SDL2/SDL.h>
#include "sisIO.hpp"

#define FPS 10
#define FRAME_TARGET 1000.0/FPS

#define WINDOW_TITLE "Snake"
#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_FLAGS SDL_WINDOW_SHOWN

#define CELL_WIDTH 40
#define CELL_HEIGHT 40
#define PADDING 10
#define START_X 0
#define START_Y CELL_HEIGHT

#define SET_DRAW_COLOR(x, y) SDL_SetRenderDrawColor(x, y.r, y.g, y.b, y.a)

class Snake {
public:
	Snake();
	bool isRunning() {return running;};

	void startFrame();
	void pollEvents();
	void update();
	void show();
	void endFrame();

	~Snake();

private:
	struct Vec2 {
	public:
		int x;
		int y;
	};

	SisIO io;

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Color backgroundColor;
	SDL_Color borderColor;
	SDL_Color snakeColor;

	bool running;
	SDL_Rect snakeHead;
	Vec2 direction;
	Uint64 startTick;
	Uint64 endTick;

	void makeCell(SDL_Rect& _rect, int _x, int _y);
	void showCell(SDL_Rect& _rect, SDL_Color& _color);

// errors
private:
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

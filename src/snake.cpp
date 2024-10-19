
#include <SDL2/SDL_ttf.h>

#include <ctime>
#include <deque>
#include <random>

#include "snake.hpp"

Snake::Snake()
    : io("./snakeLog"),
      backgroundColor{13, 13, 13, 255},
      borderColor{240, 241, 223, 255},
      snakeColor{240, 80, 79, 255},
      foodColor{247, 243, 111, 255} {
  std::srand(std::time(NULL));

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw InitError("SDL");

  if (TTF_Init() != 0) throw InitError("SDL TTF");

  window =
      SDL_CreateWindow(WINDOW_TITLE, WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH,
                       WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
  if (!window) throw InitError("SDL window");

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) throw InitError("SDL renderer");

  font = TTF_OpenFont("./font.ttf", 30);
  if (!font) throw InitError("Font");

  running = true;
  makeCell(food, RANDOM_CELL_X, RANDOM_CELL_Y);
  makeCell(snakeHead, START_X, START_Y);
  direction = {1, 0};
  alive = true;
  score = 0;

  io.output(SisIO::messageType::okay, "Game started successfully.");
}

void Snake::startFrame() { startTick = SDL_GetPerformanceCounter(); }

void Snake::pollEvents() {
  SDL_Event event = {0};
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      running = false;
      continue;
    }

    int key = -1;
    if (event.type == SDL_KEYDOWN) key = event.key.keysym.sym;

    if (key == SDLK_DOWN)
      direction = {0, 1};

    else if (key == SDLK_RIGHT)
      direction = {1, 0};

    else if (key == SDLK_LEFT)
      direction = {-1, 0};

    else if (key == SDLK_UP)
      direction = {0, -1};

    else if (key == SDLK_r && !alive)
      reset();

    else if (key == SDLK_q){
      running = false;
      continue;
    }
  }
}

void Snake::update() {
  if (!alive) return;

  snakeBody.push_front(snakeHead);
  snakeHead.x += (CELL_WIDTH * direction.x);
  snakeHead.y += (CELL_WIDTH * direction.y);

  if (snakeHead.x < START_X || snakeHead.x > WINDOW_WIDTH ||
      snakeHead.y < START_Y || snakeHead.y > WINDOW_HEIGHT) {
    alive = false;
    return;
  }

  for (SDL_Rect &body : snakeBody) {
    if (body.x == snakeHead.x && body.y == snakeHead.y) {
      alive = false;
      return;
    }
  }

  if (snakeHead.x == food.x && snakeHead.y == food.y) {
    generateFood();
    score++;
  }

  else
    snakeBody.pop_back();
}

void Snake::show() {
  if (!alive) {
    for (SDL_Rect &body : snakeBody) showCell(body, borderColor);

    SDL_RenderPresent(renderer);
    return;
  }

  SET_DRAW_COLOR(renderer, backgroundColor);
  SDL_RenderClear(renderer);

  SET_DRAW_COLOR(renderer, borderColor);
  SDL_RenderDrawLine(renderer, 0, START_Y, WINDOW_WIDTH, START_Y);

  showScore();
  showCell(food, foodColor);
  showCell(snakeHead, snakeColor);
  for (SDL_Rect &body : snakeBody) showCell(body, snakeColor);

  SDL_RenderPresent(renderer);
}

void Snake::endFrame() {
  endTick = SDL_GetPerformanceCounter();

  float elapsedMS =
      (endTick - startTick) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
  SDL_Delay(floor(FRAME_TARGET - elapsedMS));
}

void Snake::generateFood() {
  int newX;
  int newY;
  while (true) {
    bool badCoordinated = false;
    newX = RANDOM_CELL_X;
    newY = RANDOM_CELL_Y;

    int testX = newX + PADDING / 2;
    int testY = newY + PADDING / 2;

    for (SDL_Rect &rect : snakeBody) {
      if (rect.x == testX && rect.y == testY) badCoordinated = true;
    }

    if (!badCoordinated) break;
  }

  makeCell(food, newX, newY);

  io.output(SisIO::messageType::info, "Generated food at [" +
                                          std::to_string(newX) + " " +
                                          std::to_string(newY) + "]");
}

void Snake::makeCell(SDL_Rect &_rect, int _x, int _y) {
  _rect.x = _x + (PADDING / 2);
  _rect.y = _y + (PADDING / 2);
  _rect.w = CELL_WIDTH - PADDING;
  _rect.h = CELL_HEIGHT - PADDING;
}

void Snake::showCell(SDL_Rect &_rect, SDL_Color &_color) {
  SET_DRAW_COLOR(renderer, _color);
  SDL_RenderFillRect(renderer, &_rect);
  SDL_RenderDrawRect(renderer, &_rect);
}

void Snake::showScore() {
  SET_DRAW_COLOR(renderer, backgroundColor);
  std::string scoreText = "Score: " + std::to_string(score);
  SDL_Surface *scoreSurface =
      TTF_RenderText_Solid(font, scoreText.c_str(), borderColor);
  SDL_Texture *scoreTexture =
      SDL_CreateTextureFromSurface(renderer, scoreSurface);
  SDL_Rect scoreRect{0, 0, scoreSurface->w, scoreSurface->h};
  SDL_RenderCopy(renderer, scoreTexture, &scoreRect, &scoreRect);
  SDL_RenderDrawRect(renderer, &scoreRect);
}

void Snake::reset() {
  makeCell(food, RANDOM_CELL_X, RANDOM_CELL_Y);
  makeCell(snakeHead, START_X, START_Y);
  snakeBody.clear();
  direction = {1, 0};
  alive = true;
  score = 0;
  io.output(SisIO::messageType::okay, "Game restarted.");
}

Snake::~Snake() {
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
  io.output(SisIO::messageType::okay, "Game ended successfully.");
}

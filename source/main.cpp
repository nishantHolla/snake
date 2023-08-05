
#include <iostream>
#include "snake.hpp"

const char *shiftArgs(int *_argcPtr, char **_argvPtr[]);

int main(int argc, char *argv[]) {
	const char *program = shiftArgs(&argc, &argv);

	Snake game;

	while (game.isRunning()) {
		game.startFrame();
		game.pollEvents();
		game.update();
		game.show();
		game.endFrame();
	}

	return 0;
}

const char *shiftArgs(int *_argcPtr, char **_argvPtr[]) {
	(*_argcPtr)--;
	const char *arg = (*_argvPtr)[0];
	(*_argvPtr)++;
	return arg;
}

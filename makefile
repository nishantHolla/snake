
CC=clang++
FLAGS=`pkg-config --libs sdl2`
DEBUG_FLAGS=-O0 -g -Wall -Wextra -pedantic
RELEASE_FLAGS=-O3

SOURCE_DIR=./source
INCLUDE_DIR=$(SOURCE_DIR)/include
LIBRARY_DIR=$(SOURCE_DIR)/library

PROJECT_NAME=snake
SOURCE=$(SOURCE_DIR)/main.cpp $(SOURCE_DIR)/snake.cpp
OUTPUT=./output/$(PROJECT_NAME)
LIBRARIES=-lsisIO `pkg-config --cflags sdl2` -lSDL2_ttf

debug:
	$(CC) $(SOURCE) $(FLAGS) $(DEBUG_FLAGS) -I$(INCLUDE_DIR) -L$(LIBRARY_DIR) $(LIBRARIES) -o $(OUTPUT)

release:
	$(CC) $(SOURCE) $(FLAGS) $(RELEASE_FLAGS) $(DEBUG_FLAGS) -I$(INCLUDE_DIR) -L$(LIBRARY_DIR) $(LIBRARIES) -o $(OUTPUT)

SOURCES = $(wildcard src/*.cpp)

LIB_INCLUDES = ./lib/include/
LIB_CPP_SOURCES = $(wildcard lib/src/*.cpp)
LIB_C_SOURCES = $(wildcard lib/src/*.c)
LIB_BINS = ./lib/bin/

CC = g++
CFLAGS = -std=c++20
LFLAGS = -lglfw3 -lopengl32 -lgdi32

OUTPUT = bin/Mingine.exe

build: $(SOURCES) $(LIB_CPP_SOURCES) $(LIB_C_SOURCES)
	$(CC) $^ -I$(LIB_INCLUDES) -L$(LIB_BINS) $(LFLAGS) $(CFLAGS) -o $(OUTPUT) 

run: build
	$(OUTPUT)
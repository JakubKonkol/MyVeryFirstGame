CXXFLAGS = -Isdl/Include -Isrc -std=c++17 -pthread
LDFLAGS = -Lsrc
# Windows
ifeq ($(OS),Windows_NT)
	RM = del /q /f
	EXECUTABLE = game.exe
	FLAGS = -lmingw32 -lSDL2main -lSDL2
# MacOS
else ifeq ($(shell uname), Darwin)
	SDL2_INCLUDE_PATH = /usr/local/opt/sdl2/include
	SDL2_LIB_PATH = /usr/local/opt/sdl2/lib
	RM = rm -f
	EXECUTABLE = game
	FLAGS = -lSDL2main -lSDL2
	CXXFLAGS += -I$(SDL2_INCLUDE_PATH)
	LDFLAGS += -L$(SDL2_LIB_PATH)
else
	RM = rm -f
	EXECUTABLE = game
	FLAGS = -lSDL2main -lSDL2
endif

all: build

build: main.cpp
	g++ $(CXXFLAGS) $(LDFLAGS) -o $(EXECUTABLE) main.cpp $(FLAGS)
	./$(EXECUTABLE)

clean:
	$(RM) $(EXECUTABLE)

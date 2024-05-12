CXXFLAGS = -Isdl/Include -Isrc -std=c++17 -pthread
LDFLAGS = -Lsdl/lib -Lsrc
ifeq ($(OS),Windows_NT)
	RM = del /q /f
	EXECUTABLE = game.exe
	FLAGS = -lmingw32 -lSDL2main -lSDL2
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
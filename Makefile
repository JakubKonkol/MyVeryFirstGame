CXXFLAGS = -Isdl/Include -Isrc -std=c++17 -pthread
LDFLAGS = -Lsdl/lib -Lsrc
ifeq ($(OS),Windows_NT)
	RM = del /q /f
	EXECUTABLE = game.exe
else
	RM = rm -f
	EXECUTABLE = game
endif

all: build

build: main.cpp
	g++ $(CXXFLAGS) $(LDFLAGS) -o $(EXECUTABLE) main.cpp -lmingw32 -lSDL2main -lSDL2
	./$(EXECUTABLE)

clean:
	$(RM) $(EXECUTABLE)
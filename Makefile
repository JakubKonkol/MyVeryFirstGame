ifeq ($(OS),Windows_NT)
	RM = del /q /f
	EXECUTABLE = game.exe
else
	RM = rm -f
	EXECUTABLE = game
endif

all: build

build: main.cpp
	g++ -Isrc/Include -Lsrc/lib -o $(EXECUTABLE) main.cpp -lmingw32 -lSDL2main -lSDL2
	./$(EXECUTABLE)

clean:
	$(RM) $(EXECUTABLE)

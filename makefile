CFLAGS := -std=c++20
# DEBUG := -fdiagnostics-color=always -g
LIBS := -lSDL2
MAIN := main.cpp
DEPENDENCY := game.cpp

all: main.cpp game.cpp
	$(CXX) $(DEBUG) $(MAIN) $(DEPENDENCY) $(CFLAGS) $(LIBS) -o main.o

clean:
	rm -f *.o all
CFLAGS := -std=c++20
# DEBUG := -fdiagnostics-color=always -g
LIBS := -lSDL2
MAIN := main.cpp
DEPENDENCY := GUI.cpp board.cpp

default: main.cpp GUI.cpp board.cpp
	$(CXX) $(DEBUG) $(MAIN) $(DEPENDENCY) $(CFLAGS) $(LIBS) -o main.o

clean:
	rm -f *.o all
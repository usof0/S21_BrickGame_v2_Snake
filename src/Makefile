# Flags for GTK+
GTK_CFLAGS := $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS := $(shell pkg-config --libs gtk+-3.0)

# Compiling the game
all: main

main: main.o GameView.o SnakeGame.o GameController.o FSM.o
	# Tab here
	g++ -std=c++17 -o main main.o GameView.o SnakeGame.o GameController.o FSM.o $(GTK_LIBS)

main.o: main.cpp
	# Tab here
	g++ -std=c++17 -c main.cpp $(GTK_CFLAGS)

GameView.o: gui/desktop/GameView.cpp
	# Tab here
	g++ -std=c++17 -c gui/desktop/GameView.cpp $(GTK_CFLAGS)

SnakeGame.o: brick_game/snake/SnakeGame.cpp
	# Tab here
	g++ -std=c++17 -c brick_game/snake/SnakeGame.cpp

GameController.o: gui/desktop/GameController.cpp
	# Tab here
	g++ -std=c++17 -c gui/desktop/GameController.cpp

FSM.o: brick_game/snake/FSM.cpp
	# Tab here
	g++ -std=c++17 -c brick_game/snake/FSM.cpp

clean:
	# Tab here
	rm -f *.o main

SRC=net.cc neuron.cc test.cc
DEBUG_FLAG=-g
CC=gcc
FLAGS=-Wall -Werror -Wextra -lstdc++ -std=c++17

build:
	  $(CC) $(FLAGS) $(SRC)

test: build
	./a.out

debug:
	$(CC) $(FLAGS) $(SRC) $(DEBUG_FLAG)
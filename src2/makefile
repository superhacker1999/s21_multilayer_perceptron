SRC=net.cc neuron.cc test.cc parser.cc
DEBUG_FLAG=-g
CC=gcc
FLAGS=-Wall -Wextra -lstdc++ -std=c++17

build: clean
	  $(CC) $(FLAGS) $(SRC)

test: build
	./a.out > output.txt

debug: clean
	$(CC) $(FLAGS) $(SRC) $(DEBUG_FLAG)

clean:
	rm -rf a.out*
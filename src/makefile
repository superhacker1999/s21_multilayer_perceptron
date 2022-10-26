CC=gcc
SRC:=$(PWD)/code/* $(PWD)/helpers/parser.cc
CFLAGS:=-Wall -Wextra -lstdc++ -std=c++17

test: clean
	$(CC) $(CFLAGS) $(SRC)
	./a.out > output.txt

debug: clean
	$(CC) $(CFLAGS) -g $(SRC)

clean:
	rm -rf output.txt
	rm -rf a.out*

CC=gcc
SRC:=$(PWD)/code/* $(PWD)/helpers/parser.cc
CFLAGS:=-Wall -Wextra -lstdc++ -std=c++17

learn: clean
	$(CC) $(CFLAGS) $(SRC)
	./a.out > output.txt

test:
	$(CC) $(CFLAGS) $(SRC)
	./a.out

debug: clean
	$(CC) $(CFLAGS) -g $(SRC)

clean:
	rm -rf output.txt
	rm -rf a.out*

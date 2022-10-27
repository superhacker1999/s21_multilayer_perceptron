CC=gcc
SRC_LEARN:=code/layer.cc code/network.cc code/neuron.cc code/learn.cc $(PWD)/helpers/parser.cc
SRC_TEST:=code/layer.cc code/network.cc code/neuron.cc code/test.cc $(PWD)/helpers/parser.cc
CFLAGS:=-Wall -Wextra -lstdc++ -std=c++17

learn: clean
	$(CC) $(CFLAGS) $(SRC_LEARN)
	./a.out $(settings) > text.txt
	bash telegram.sh "Neuron net has trained."
	rm -rf text.txt

test:
	$(CC) $(CFLAGS) $(SRC_TEST)
	./a.out $(filename) > text.txt
	bash telegram.sh "Tests are done."
	rm -rf text.txt

debug: clean
	$(CC) $(CFLAGS) -g $(SRC)

clean:
	rm -rf output.txt
	rm -rf a.out*

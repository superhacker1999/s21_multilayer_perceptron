CC=gcc
SRC_LEARN:=code/layer.cc code/network.cc code/neuron.cc code/learn.cc $(PWD)/helpers/parser.cc
SRC_TEST:=code/test.cc 
SRC:=code/layer.cc code/network.cc code/neuron.cc $(PWD)/helpers/parser.cc
SRC_GUI_TEST:=tests/test_from_interface.cc helpers/datahandler.cc
CFLAGS:=-Wall -Wextra -lstdc++ -std=c++17

learn: clean
	$(CC) $(CFLAGS) $(SRC_LEARN) -g
	./a.out $(alpha) $(percent) $(epochs) > text.txt
	bash telegram.sh "Neuron net has trained."
	echo cat text.txt | tail -n1
	rm -rf text.txt

test:
	$(CC) $(CFLAGS) $(SRC_TEST) $(SRC)
	./a.out $(filename) > text.txt
	bash telegram.sh "Tests are done."
	rm -rf text.txt

gui_test:
	$(CC) $(CFLAGS) -g $(SRC) $(SRC_GUI_TEST)
	./a.out /Users/ritapryanik/Desktop/mlp/src/weights/weights26640x100x005.txt

debug: clean
	$(CC) $(CFLAGS) -g $(SRC)

clean:
	rm -rf output.txt
	rm -rf a.out*
	rm -rf text.txt

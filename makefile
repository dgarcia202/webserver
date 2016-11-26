all:
	g++ -g -Wall -pedantic -std=c++11 main.cpp webserver.cpp socketCtrl.cpp logger.cpp -o webserver.exe -lws2_32

clean:
	rm webserver.exe	
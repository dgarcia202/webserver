all:
	g++ -g -Wall -pedantic main.cpp dynws.cpp socket.cpp logger.cpp -o dynws.exe -lws2_32

clean:
	rm DynWS.exe	
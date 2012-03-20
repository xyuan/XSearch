main: main.o url.o
	g++ -o main main.o url.o
main.o: main.cpp url.cpp
	g++ -c main.cpp
url.o: url.cpp url.h
	g++ -c url.cpp

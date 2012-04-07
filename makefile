main: main.o url.o stringfun.o
	g++ -o main main.o url.o
main.o: main.cpp url.cpp
	g++ -c main.cpp
url.o: url.cpp url.h
	g++ -c url.cpp
stringfun.o: stringfun.cpp stringfun.h
	g++ -c stringfun.cpp

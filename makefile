main: main.o url.o stringfun.o
	g++ -o main main.o url.o stringfun.o
main.o: main.cpp url.cpp stringfun.cpp
	g++ -c main.cpp
url.o: url.cpp url.h
	g++ -c url.cpp
stringfun.o: stringfun.cpp stringfun.h
	g++ -c stringfun.cpp

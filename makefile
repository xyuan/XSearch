main: main.o url.o stringfun.o searchfile.o dataengine.o fileengine.o
	g++ -o main main.o url.o stringfun.o searchfile.o dataengine.o fileengine.o
main.o: main.cpp
	g++ -c $^
url.o: url.cpp
	g++ -c $^
stringfun.o: stringfun.cpp
	g++ -c $^
dataengine.o: dataengine.cpp
	g++ -c $^
fileengine.o: fileengine.cpp
	g++ -c $^
searchfile.o: searchfile.cpp
	g++ -c $^

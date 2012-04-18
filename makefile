main: main.o url.o stringfun.o searchfile.o dataengine.o fileengine.o page.o linkfile.o crawler.o
	g++ -o main main.o url.o stringfun.o searchfile.o dataengine.o fileengine.o page.o linkfile.o crawler.o
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
linkfile.o: linkfile.cpp
	g++ -c $^
page.o: page.cpp
	g++ -c $^
crawler.o: crawler.cpp
	g++ -c $^

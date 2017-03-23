all: edge graph main clean 

edge: Edge.h
	g++ -Wall -Werror -c Edge.cpp
graph: Graph.h
	g++ -Wall -Werror -c Graph.cpp
main: Graph.o main.cpp
	g++ -Wall -Werror -o main Edge.o Graph.o main.cpp
clean: Graph.o Edge.o
	rm Graph.o Edge.o

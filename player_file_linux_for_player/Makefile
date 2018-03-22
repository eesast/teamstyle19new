STD=-std=c++11
%.o:%.cpp
	g++ -c $< $(STD) -o $@

all:re

main.o:main.cpp

communication.o:communication.cpp 

player.o:player.cpp

api_player.o:api_player.cpp api_player.h

re:main.o communication.o player.o api_player.o
	g++ $^ -std=c++11 -pthread -o $@

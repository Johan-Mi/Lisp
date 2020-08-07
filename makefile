CC = g++
CPPFLAGS = -O3 -Wall -std=c++20

main: main.o types.o functions.o
	${CC} ${CPPFLAGS} -o main main.o types.o functions.o

main.o: main.cpp types.hpp functions.hpp
	${CC} ${CPPFLAGS} -c main.cpp

types.o: types.cpp types.hpp
	${CC} ${CPPFLAGS} -c types.cpp

functions.o: functions.cpp functions.hpp types.hpp
	${CC} ${CPPFLAGS} -c functions.cpp

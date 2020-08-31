CC = g++
CPPFLAGS = -O3 -Wall -std=c++20
# CPPFLAGS = -g -Wall -std=c++20

main: main.o functions.o to-string.o parser.o lexer.o wrapped.o
	${CC} ${CPPFLAGS} -o main main.o functions.o to-string.o parser.o lexer.o wrapped.o

main.o: main.cpp types.hpp functions.hpp to-string.hpp parser.hpp lexer.hpp wrapped.hpp
	${CC} ${CPPFLAGS} -c main.cpp

functions.o: functions.cpp functions.hpp types.hpp
	${CC} ${CPPFLAGS} -c functions.cpp

to-string.o: to-string.cpp to-string.hpp types.hpp functions.hpp
	${CC} ${CPPFLAGS} -c to-string.cpp

lexer.o: lexer.cpp lexer.hpp types.hpp
	${CC} ${CPPFLAGS} -c lexer.cpp

parser.o: parser.cpp parser.hpp types.hpp
	${CC} ${CPPFLAGS} -c parser.cpp

wrapped.o: wrapped.cpp wrapped.hpp types.hpp functions.hpp
	${CC} ${CPPFLAGS} -c wrapped.cpp

clean:
	rm -f main *.o

.PHONY: clean

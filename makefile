CC = g++
CFLAGS = -Wall

MAIN = main.o

MATRIX_DEPS = matrix/matrix.hpp
 
DEPS = ${MATRIX_DEPS}

clear:
	bash -c "clear"

main: ${MAIN} ${DEPS}
	${CC} -o main ${MAIN} ${CFLAGS}

clean:
	rm -f ${MAIN} 

all: clear main clean

.PHONY: clear clean main all


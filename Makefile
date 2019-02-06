# Makefile 
# Program 2
#
# Author: JT Mundi
#
# Compile: make
# Run    : make run
# Clean  : make clean

CPP = gcc
FLAGS = -Wall -g -std=c99 -pedantic 

EXEC = ok
OBJS = ok.o

PROJECT_NAME = PROGRAM_5
FILES = ok.c Makefile

default:${EXEC}

all:${EXEC}

clean:
	rm -f ${EXEC}
	rm -f *.o

run: ${EXEC}
	./${EXEC}

${EXEC}:${OBJS}
	${CPP} ${FLAGS} -o ${EXEC} ${OBJS}

tar:
	tar -cvf ${PROJECT_NAME}.tgz ${FILES}


.c.o:
	${CPP} ${FLAGS} -c $<

ok.o: ok.c

PROGRAM = shoot

SOURCE = root.cc
OBJECT = $(SOURCE:.cc=.o)

GXX = g++
FLAGS = -W -Wall -Werror -pedantic
DEBUG = -g -ggdb
CFLAGS = `sdl-config --cflags`
LFLAGS = `sdl-config --libs`

.PHONY: clean all

all: ${PROGRAM}

${PROGRAM}: ${OBJECT}
	${GXX} ${FLAGS} ${DEBUG} ${LFLAGS} ${OBJECT} -o ${PROGRAM}

.SUFFIXES: .cc .o

.cc:
	${GXX} ${FLAGS} ${DEBUG} ${CFLAGS} ${LFLAGS} $< -o $@

.cc.o:
	${GXX} ${FLAGS} ${DEBUG} ${CFLAGS} -c $< -o $@

clean:
	@rm -rf ${PROGRAM}
	@find . -name '*.o' -delete -print
	@find . -name '*~' -delete -print
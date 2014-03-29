PROGRAM = shoot

SOURCE = firstpstate.cc gameengine.cc menustate.cc pausestate.cc physengine.cc player.cc root.cc weapon.cc
OBJECT = $(SOURCE:.cc=.o)

GXX = g++
FLAGS = -W -Wall -Werror -pedantic
DEBUG = -g -ggdb
CFLAGS = `sdl-config --cflags`
LFLAGS = `sdl-config --libs` -lSDL_image

.PHONY: clean all

all: media ${PROGRAM}

${PROGRAM}: ${OBJECT}
	${GXX} ${FLAGS} ${DEBUG} ${LFLAGS} ${OBJECT} -o ${PROGRAM}

.SUFFIXES: .cc .o

.cc:
	${GXX} ${FLAGS} ${DEBUG} ${CFLAGS} ${LFLAGS} $< -o $@

.cc.o:
	${GXX} ${FLAGS} ${DEBUG} ${CFLAGS} -c $< -o $@

media:
	@if [ -d media ]; then touch media; else wget https://dl.dropboxusercontent.com/u/30048549/ProjectMedia/iwannacookie/media.zip; fi
	@unzip media.zip
	@rm media.zip

clean:
	@rm -rf ${PROGRAM}
	@find . -name '*.o' -delete -print
	@find . -name '*~' -delete -print

#EOF
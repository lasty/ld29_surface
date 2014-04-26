
.PHONY: all
all: BeneathTheSurface

SDL_SRCS=sdl_exception.cpp sdl_init.cpp window.cpp
MAIN_SRCS=main.cpp

VPATH=src:src/sdl
CFLAGS+="-Isrc"

SRCS=${SDL_SRCS} ${MAIN_SRCS}

OBJS=${SRCS:.cpp=.o}
DEPS=${SRCS:.cpp=.d}

#Requires GCC 4.8.1 or above, or clang
CXXFLAGS+=-std=c++11

#TODO system specifics, for now it's just linux
UNAME:=${shell uname}

SDL_INCPATH=-I/usr/include/SDL2
SDL_LIBPATH=
SDL_LIBS=-lSDL2 -lSDL2_image -lSDL2_mixer

CFLAGS+=${SDL_INCPATH}
LDFLAGS+=${SDL_LIBPATH} ${SDL_LIBS}

FREETYPE_INCPATH=-I/usr/include/freetype2
FREETYPE_LIBPATH=
FREETYPE_LIBS=-lfreetype

CFLAGS+=${FREETYPE_INCPATH}
LDFLAGS+=${FREETYPE_LIBPATH} ${FREETYPE_LIBS}


%.o: %.cpp
	${CXX} -MMD -MP -c ${CFLAGS} ${CXXFLAGS} -o $@ $<

BeneathTheSurface: ${OBJS}
	${CXX} $^ ${LDFLAGS} -o $@

.PHONY: clean
clean:
	${RM} BeneathTheSurface
	${RM} ${OBJS} ${DEPS}

#include dependency files created with -MMD -MP flags above
-include ${DEPS}


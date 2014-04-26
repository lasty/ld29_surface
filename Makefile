
.PHONY: all
all: BeneathTheSurface


SDL_SRCS=
MAIN_SRCS=main.cpp

SRCS=${SDL_SRCS} ${MAIN_SRCS}

OBJS=${SRCS:.cpp=.o}
DEPS=${SRCS:.cpp=.d}


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


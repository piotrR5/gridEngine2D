all:
	g++ main.cpp src/cell.hpp src/grid.cpp src/grid.hpp src/engine.cpp src/engine.hpp -lSDL2 -o engine.out -Wall -Werror -Wno-error=maybe-uninitialized

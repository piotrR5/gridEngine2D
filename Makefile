all: clean
	g++ main.cpp src/cell.hpp src/grid.cpp src/grid.hpp src/engine.cpp src/engine.hpp -lSDL2 -lSDL2_image -o engine.out -Wall -Werror -Wno-error=maybe-uninitialized -Wno-error=unused-result -O3
prof: clean
	g++ main.cpp src/cell.hpp src/grid.cpp src/grid.hpp src/engine.cpp src/engine.hpp -lSDL2 -lSDL2_image -o engine.out -Wall -Werror -pg -Wno-error=maybe-uninitialized -Wno-error=unused-result
	./engine.out
	gprof ./engine.out gmon.out > profOut.txt
	less profOut.txt
clean:
	rm -f profOut.txt engine.out gmon.out

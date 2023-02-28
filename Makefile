all: clean
	g++ main.cpp src/cell.hpp src/grid.cpp src/grid.hpp src/engine.cpp src/engine.hpp src/parser.cpp src/parser.hpp src/gui.cpp src/gui.hpp -lSDL2 -lSDL2_image -lSDL2_ttf -o engine.out -Wall -Werror -Wno-error=maybe-uninitialized -Wno-error=unused-result -O3
prof: clean
	g++ main.cpp src/cell.hpp src/grid.cpp src/grid.hpp src/engine.cpp src/engine.hpp src/parser.cpp src/parser.hpp src/gui.cpp src/gui.hpp -lSDL2 -lSDL2_image -lSDL2_ttf -o engine.out -Wall -Werror -pg -Wno-error=maybe-uninitialized -Wno-error=unused-result
	./engine.out
	gprof ./engine.out gmon.out > profOut.txt
	less profOut.txt
clean:
	rm -f profOut.txt engine.out gmon.out
run: all
	./engine.out

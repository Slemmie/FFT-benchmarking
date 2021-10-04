
INCLUDE = -I .
SRC = \
./driver.cpp \
./program_wrappers/program_pool.cpp \
./validator_implementation/FFT.cpp \
./variations/FFT.cpp

all: release

generator:
	g++ -Wall -std=c++17 ./generators/gen.cpp -o gen -O2 $(INCLUDE)

debug:
	g++ -Wall -std=c++17 $(SRC) -o driver -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG $(INCLUDE)

release:
	g++ -Wall -std=c++17 $(SRC) -o driver -O2 $(INCLUDE)

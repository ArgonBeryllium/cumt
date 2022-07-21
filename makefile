SHELL=/bin/bash

CXX=clang++
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
CXX_FLAGS=--std=c++17 -g

TEST_SRC=$(wildcard src/*.cpp)
TEST_BIN=bin/test

test: $(TEST_BIN)

$(TEST_BIN): $(wildcard src/*)
	[ -e bin ] || mkdir bin
	$(CXX) $(TEST_SRC) $(LIBS) $(CXX_FLAGS) -o $(TEST_BIN)

MINGW=x86_64-w64-mingw32-g++
MINGW_FLAGS=-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -O3

test-win: $(wildcard src/*)
	[ -e bin ] || mkdir bin
	$(MINGW) $(TEST_SRC) $(LIBS) $(CXX_FLAGS) $(MINGW_FLAGS) -o bin/test.exe

LIB_SRC=$(wildcard src/cumt*.cpp)
LIB_BIN=bin/lib/libcumt.so

lib: $(LIB_BIN)

$(LIB_BIN): $(wildcard src/cumt*)
	[ -e bin/lib ] || mkdir -p bin/lib
	$(CXX) $(LIB_SRC) -c $(LIBS) $(CXX_FLAGS) -fPIC
	mv *.o bin/lib
	$(CXX) -shared bin/lib/*.o $(LIBS) -o $(LIB_BIN)

install: lib
	sudo cp bin/lib/libcumt.so /usr/lib/
	[ -e /usr/include/cumt ] || sudo mkdir /usr/include/cumt
	sudo cp src/cumt*.h /usr/include/cumt/
	sudo chmod a=rw /usr/include/cumt/*

clean:
	rm bin/* -rf

uninstall:
	sudo rm /usr/include/cumt/ -rf
	sudo rm /usr/lib/libcumt.so -f

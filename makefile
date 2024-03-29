SHELL=/bin/bash

CXX=clang++
LIBS=-Wl,-Bdynamic -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
CXX_FLAGS=--std=c++17 -g

# Test executables

# normal people
TEST_SRC=$(wildcard src/*.cpp)
TEST_BIN=bin/test

test: $(TEST_BIN)

$(TEST_BIN): $(wildcard src/*)
	[ -e bin ] || mkdir bin
	$(CXX) $(TEST_SRC) $(LIBS) $(CXX_FLAGS) -o $(TEST_BIN)

# windows users
MINGW=x86_64-w64-mingw32-g++
MINGW_LIBS=-Wl,-Bstatic -lstdc++ -lpthread -static-libgcc -static-libstdc++
MINGW_FLAGS=-mwindows
TEST_BIN_WIN=bin/win/test.exe

test-win: $(TEST_BIN_WIN)

$(TEST_BIN_WIN): $(wildcard src/*)
	[ -e bin ] || mkdir bin
	$(MINGW) $(TEST_SRC) $(MINGW_FLAGS) $(MINGW_LIBS) $(CXX_FLAGS) $(LIBS) -o $(TEST_BIN_WIN)

# Library binaries

LIB_SRC=$(wildcard src/cumt*.cpp)
LIB_BIN=bin/lib/libcumt.so
LIB_BIN_STATIC=bin/lib/libcumt.a

lib: $(LIB_BIN)

$(LIB_BIN): $(wildcard src/cumt*) src/shitrndr/src/shitrndr.h
	[ -e bin/lib ] || mkdir -p bin/lib
	$(CXX) $(LIB_SRC) -c $(LIBS) $(CXX_FLAGS) -fPIC
	mv *.o bin/lib
	$(CXX) -shared bin/lib/*.o $(LIBS) -o $(LIB_BIN)

lib_static: $(LIB_BIN_STATIC)

$(LIB_BIN_STATIC): $(wildcard src/cumt*) src/shitrndr/src/shitrndr.h
	[ -e bin/lib ] || mkdir -p bin/lib
	$(CXX) $(LIB_SRC) -c $(LIBS) $(CXX_FLAGS) -fPIC
	mv *.o bin/lib
	ar rc $(LIB_BIN_STATIC) bin/lib/*.o

# Other

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

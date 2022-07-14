SHELL=/bin/bash

CXX=clang++
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
CXX_FLAGS=--std=c++17 -O3

test: src/*
	[ -e bin ] || mkdir bin
	$(CXX) src/*.cpp -c $(CXX_FLAGS)
	mv *.o bin/
	$(CXX) bin/*.o $(LIBS) $(CXX_FLAGS) -o bin/test

MINGW=x86_64-w64-mingw32-g++
MINGW_FLAGS=-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -O3

test-win: src/*
	[ -e bin ] || mkdir bin
	$(MINGW) src/*.cpp $(LIBS) $(CXX_FLAGS) $(MINGW_FLAGS) -o bin/test.exe


lib: src/cumt*
	[ -e bin/lib ] || mkdir bin/lib
	$(CXX) src/cumt*.cpp -c $(LIBS) $(CXX_FLAGS) -fPIC
	mv *.o bin/lib
	$(CXX) -shared bin/lib/*.o $(LIBS) -o bin/lib/libcumt.so

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

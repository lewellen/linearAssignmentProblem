libObjs = $(patsubst lib/%.cpp, obj/lib/%.o, $(wildcard lib/*.cpp))
bins = $(patsubst src/%.cpp, bin/%, $(wildcard src/*.cpp))

cppTool = g++
cppFlags = -O3 -Wall -Wno-unused-variable -Wno-narrowing -Wno-sign-compare 

.PHONY: all clean

all: $(bins)

runtime.png: obj/runtime.dat src/runtime.gpi
	gnuplot src/runtime.gpi

obj/runtime.dat: bin/runtimeProfile
	bin/runtimeProfile > obj/runtime.dat

bin/%: obj/src/%.o obj/lib.o | bin
	$(cppTool) $(cppFlaggs) obj/lib.o $< -o $@

bin:
	mkdir -p ./bin

obj/lib.o: $(libObjs)
	ld -r $(libObjs) -o obj/lib.o

obj/src/%.o: src/%.cpp | obj/src
	$(cppTool) $(cppFlags) -I./include -c $< -o $@

obj/lib/%.o: lib/%.cpp | obj/lib
	$(cppTool) $(cppFlags) -I./include -c $< -o $@

obj/src: | obj
	mkdir -p ./obj/src

obj/lib: | obj
	mkdir -p ./obj/lib

obj:
	mkdir -p ./obj

clean:
	rm -rf obj
	rm -rf bin
